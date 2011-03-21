/*
 * 
 */
package com.xoomcode.acidmaps;

import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.imageio.ImageIO;
import javax.servlet.ServletException;

import org.geoserver.platform.ServiceException;
import org.geoserver.wms.GetMapRequest;
import org.geoserver.wms.MapLayerInfo;
import org.geoserver.wms.WMSMapContext;
import org.geoserver.wms.WebMap;
import org.geoserver.wms.map.RenderedImageMap;
import org.geotools.data.FeatureSource;
import org.geotools.factory.CommonFactoryFinder;
import org.geotools.factory.GeoTools;
import org.geotools.feature.FeatureCollection;
import org.geotools.feature.FeatureIterator;
import org.geotools.styling.FeatureTypeConstraint;
import org.geotools.util.logging.Logging;
import org.opengis.feature.Feature;
import org.opengis.feature.Property;
import org.opengis.feature.simple.SimpleFeature;
import org.opengis.feature.type.FeatureType;
import org.opengis.feature.type.GeometryDescriptor;
import org.opengis.filter.Filter;
import org.opengis.filter.FilterFactory;

import com.vividsolutions.jts.geom.Point;
import com.xoomcode.acidmaps.adapter.JCAdapter;
import com.xoomcode.acidmaps.cache.DatasetCache;
import com.xoomcode.acidmaps.cache.DatasetCacheKey;
import com.xoomcode.acidmaps.constants.ErrorConstants;
import com.xoomcode.acidmaps.core.AcidMapParameters;
import com.xoomcode.acidmaps.core.Bounds;
import com.xoomcode.acidmaps.core.Color;
import com.xoomcode.acidmaps.core.Configuration;
import com.xoomcode.acidmaps.error.AcidMapException;
import com.xoomcode.acidmaps.error.ErrorImageFactory;
import com.xoomcode.acidmaps.error.Validator;

// TODO: Auto-generated Javadoc
/**
 * The Class AcidMapService.
 * 
 * This class process the Acid Map Service request and
 * return the map
 *
 * @date 09/11/2010
 * @author cfarina
 * The Class AcidMapService.
 */
public class AcidMapService {
	
	/** The Constant LOGGER. */
	private final static Logger LOGGER = Logging.getLogger(AcidMapService.class.toString());
	
	/** The dataset cache. */
	private static DatasetCache datasetCache = new DatasetCache();
	
	/** The filter factory. */
	private FilterFactory filterFactory;
	
	private ErrorImageFactory errorImageFactory = new ErrorImageFactory();
	
	/**
	 * Instantiates a new acid map service.
	 */
	public AcidMapService() {
		this.filterFactory = CommonFactoryFinder.getFilterFactory(GeoTools.getDefaultHints());
	}
	
	/**
	 * Sets the filter factory.
	 *
	 * @param filterFactory the new filter factory
	 */
	public void setFilterFactory(final FilterFactory filterFactory) {
        this.filterFactory = filterFactory;
    }

	/**
	 * Gets the map.
	 *
	 * @param request the request
	 * @return the web map
	 * @throws ServletException the servlet exception
	 * @throws IOException Signals that an I/O exception has occurred.
	 * @throws AcidMapException the acid map exception
	 */
	public WebMap GetMap(GetMapRequest request) throws ServletException,
			IOException, AcidMapException {
		WMSMapContext mapContext = new WMSMapContext(request);
		try {
			if (request.getLayers() != null && request.getLayers().size() > 0) {
				
				LOGGER.log(Level.WARNING, "Processing request " + request.getRawKvp().toString());
				
				MapLayerInfo layer = request.getLayers().get(0);
				
				DatasetCacheKey datasetCacheKey = new DatasetCacheKey(layer.getName(), getStringFilter(request));
				/*
				 * In order to avoid to get all the points for each tile a synchronized method is 
				 * invoked. Once that the first execution of synchronizedRun has been executed
				 * the data is cached, and the next time this method is invoked, it uses the cached data.
				 */
				if(datasetCache.isCached(datasetCacheKey)){
					return run(request, mapContext);
				} else {
					return synchronizedRun(request, mapContext);
				}
			}
			return null;
		} catch (ServiceException e) {
			mapContext.dispose();
			LOGGER.log(Level.SEVERE, e.getMessage(), e);
			return buildErrorImage(request, mapContext, e);
		} catch (RuntimeException e) {
			mapContext.dispose();
			LOGGER.log(Level.SEVERE, e.getMessage(), e);
			return buildErrorImage(request, mapContext, e);
		} catch (AcidMapException e) {
			mapContext.dispose();
			LOGGER.log(Level.SEVERE, e.getMessage(), e);
			return buildErrorImage(request, mapContext, e);
		} catch (Exception e) {
			mapContext.dispose();
			LOGGER.log(Level.SEVERE, e.getMessage(), e);
			return buildErrorImage(request, mapContext, e);
		} 
	}

	/**
	 * When the data to be interpolated are not cached, this method is invoked.
	 * Because of this method is synchronized, all invocations of this will be glued.
	 * The first invocation of this method caches the data. Next glued invocations
	 * will use the cached data.
	 * Return the map.
	 *
	 * @param request the request
	 * @param mapContext the map context
	 * @return the web map
	 * @throws ServiceException the service exception
	 * @throws IOException Signals that an I/O exception has occurred.
	 * @throws AcidMapException the acid map exception
	 */
	
	public synchronized WebMap synchronizedRun(final GetMapRequest request, WMSMapContext mapContext) throws ServiceException, IOException, AcidMapException {
		Map<String, String> rawKvp = request.getRawKvp();
		String valueColumn = rawKvp.get(AcidMapParameters.VALUE_COLUMN);

		MapLayerInfo layer = request.getLayers().get(0);
		
		DatasetCacheKey datasetCacheKey = new DatasetCacheKey(layer.getName(), getStringFilter(request));
		
		Filter layerFilter = buildLayersFilters(request.getFilter(), request.getLayers())[0];
		
		FeatureSource<? extends FeatureType, ? extends Feature> source = layer.getFeatureSource(true);
		FeatureType schema = source.getSchema();
		final GeometryDescriptor geometryAttribute = schema.getGeometryDescriptor();
		
		com.xoomcode.acidmaps.core.Point[] dataset = null;
		if(!datasetCache.isCached(datasetCacheKey)){
			LOGGER.log(Level.WARNING, "Cache missed");
			
			//Get the features
			FeatureCollection<? extends FeatureType, ? extends Feature> features = source.getFeatures(layerFilter);
			FeatureIterator<? extends Feature> featureIterator = features.features();
			dataset = new com.xoomcode.acidmaps.core.Point[features.size()];
			int i = 0;
			while (featureIterator.hasNext()) {
				SimpleFeature f = (SimpleFeature) featureIterator.next();
				Property theGeom = f.getProperty(geometryAttribute.getName());
				Point point = (Point)theGeom.getValue();
				com.xoomcode.acidmaps.core.Point acidMapPoint = new com.xoomcode.acidmaps.core.Point();
				acidMapPoint.x = (float)point.getX();
				acidMapPoint.y = (float)point.getY();
				
				Property value = f.getProperty(valueColumn);
				if(value != null){
					acidMapPoint.value = ((Number)value.getValue()).floatValue();
				}
				dataset [i] = acidMapPoint;
				i++;
			} 
			datasetCache.put(datasetCacheKey, dataset);
		} else {
			LOGGER.log(Level.WARNING, "Cache hint");
			
		}
		return run(request, mapContext);
	}

	
	/**
	 * Build the string filter.
	 *
	 * @param request the request
	 * @return the string filter
	 */
	private String getStringFilter(final GetMapRequest request) {
		String filter = "";
		if(request.getFilter() != null){
			filter = request.getFilter().toString();
		}
		return filter;
	}

	/**
	 * Get the data from cache, build the image and return that.
	 *
	 * @param request the request
	 * @param mapContext the map context
	 * @return the web map
	 * @throws ServiceException the service exception
	 * @throws IOException Signals that an I/O exception has occurred.
	 * @throws AcidMapException the acid map exception
	 */
	public WebMap run(final GetMapRequest request, WMSMapContext mapContext)
			throws ServiceException, IOException, AcidMapException {

		Configuration configuration = buildConfiguration(request);
		
		MapLayerInfo layer = request.getLayers().get(0);
		
		DatasetCacheKey datasetCacheKey = new DatasetCacheKey(layer.getName(), getStringFilter(request));
		
		configuration.dataset = datasetCache.getDataset(datasetCacheKey);
		configuration.datasetSize = configuration.dataset.length;
		
		int error = Validator.validate(configuration);
		if(error != 0){
			throw new AcidMapException("Opaaa. Error in acidMapsLibrary. " + ErrorConstants.getErrorString(error));
		}
		
		JCAdapter jCAdapter = new JCAdapter();
		byte[] outputBuffer = jCAdapter.interpolate(configuration);
		
		BufferedImage image=ImageIO.read(new ByteArrayInputStream(outputBuffer));
		
        final String outputFormat = request.getFormat();
        RenderedImageMap result = new RenderedImageMap(mapContext, image, outputFormat);
        return result;
		
	}
	
	/**
	 * Builds the configuration.
	 *
	 * @param request the request
	 * @return the configuration
	 * @throws AcidMapException the acid map exception
	 */
	private Configuration buildConfiguration(final GetMapRequest request) throws AcidMapException {
		Map<String, String> rawKvp = request.getRawKvp();
		int simplifyMethod = new Integer(rawKvp.get(AcidMapParameters.SIMPLIFY_METHOD));
		int simplifySize = new Integer(rawKvp.get(AcidMapParameters.SIMPLIFY_SIZE));
		float[] intervals = buildIntervals(rawKvp.get(AcidMapParameters.INTERVALS));
		Color[] intervalsColors = buildIntervalsColors(rawKvp.get(AcidMapParameters.INTERVALS_COLORS));
		int rendererType = new Integer(rawKvp.get(AcidMapParameters.RENDERER_TYPE));
		int interpolationStrategy = new Integer(rawKvp.get(AcidMapParameters.INTERPOLATION_STRATEGY));
		int radius = new Integer(rawKvp.get(AcidMapParameters.RADIUS));
		
		Configuration configuration = new Configuration();
		configuration.simplifyMethod = simplifyMethod;
		configuration.simplifySize = simplifySize;

		Bounds bounds = null;
		if(request.getBbox() != null){
			bounds = new Bounds();
			bounds.minY = (float)request.getBbox().getMinY();
			bounds.minX = (float)request.getBbox().getMinX();
			bounds.maxY = (float)request.getBbox().getMaxY();
			bounds.maxX = (float)request.getBbox().getMaxX();
		}
		configuration.bounds = bounds;
		
		configuration.width = request.getWidth();
		configuration.height = request.getHeight();
		
		configuration.intervals = intervals;
		configuration.intervalsColors = intervalsColors;
		configuration.rendererType = rendererType;
		configuration.interpolationStrategy = interpolationStrategy;
		configuration.radius = radius;
		
		return configuration;
	}
	
	/**
	 * Builds the intervals colors.
	 *
	 * @param intervalsColorStr the intervals color str
	 * @return the color[]
	 * @throws AcidMapException the acid map exception
	 */
	private Color[] buildIntervalsColors(String intervalsColorStr) throws AcidMapException {
		if(intervalsColorStr == "" || intervalsColorStr == null){
			return null;
		}
		String[] split = intervalsColorStr.split(",");
		
		Color[] intervalsColor = new Color[split.length];	
		
		for (int i = 0; i < intervalsColor.length; i++) {
			String hexaNumber = split[i].toUpperCase();
			if(hexaNumber.contains("#")){
				hexaNumber = hexaNumber.split("#")[1];
			} else if(hexaNumber.contains("X")){
				hexaNumber = hexaNumber.split("X")[1];
			} else {
				throw new AcidMapException("Malformed Color hexa number ");
			}
			int colorValue = (int)Long.parseLong(hexaNumber, 16);
			byte r = (byte) (colorValue >> 24 & 0xFF);
			byte g = (byte) (colorValue >> 16 & 0xFF);
			byte b = (byte) (colorValue >> 8 & 0xFF);
			byte a = (byte) (colorValue & 0xFF);
			
			intervalsColor[i] = new Color(r, g, b, a);
		}
		return intervalsColor;
	}

	/**
	 * Builds the intervals.
	 *
	 * @param intervalsStr the intervals str
	 * @return the float[]
	 */
	private float[] buildIntervals(String intervalsStr) {
		if(intervalsStr == "" || intervalsStr == null){
			return null;
		}
		String[] split = intervalsStr.split(",");
		
		float [] intervals = new float[split.length];	
		
		for (int i = 0; i < intervals.length; i++) {
			intervals[i] = new Float(split[i]);
		}
		return intervals;
	}

	/**
     * Returns the list of filters resulting of comining the layers definition filters with the per
     * layer filters made by the user.
     * <p>
     * If <code>requestFilters != null</code>, it shall contain the same number of elements than
     * <code>layers</code>, as filters are requested one per layer.
     * </p>
     * 
     * @param requestFilters
     *            the list of filters sent by the user, or <code>null</code>
     * @param layers
     *            the layers requested in the GetMap request, where to get the per layer definition
     *            filters from.
     * @return a list of filters, one per layer, resulting of anding the user requested filter and
     *         the layer definition filter
     */
    private Filter[] buildLayersFilters(List<Filter> requestFilters, List<MapLayerInfo> layers) {
        final int nLayers = layers.size();
        if (requestFilters == null || requestFilters.size() == 0) {
            requestFilters = Collections.nCopies(layers.size(), (Filter) Filter.INCLUDE);
        } else if (requestFilters.size() != nLayers) {
            throw new IllegalArgumentException(
                    "requested filters and number of layers do not match");
        }
        Filter[] combinedList = new Filter[nLayers];
        Filter layerDefinitionFilter;
        Filter userRequestedFilter;
        Filter combined;

        MapLayerInfo layer;
        for (int i = 0; i < nLayers; i++) {
            layer = layers.get(i);
            userRequestedFilter = requestFilters.get(i);
            if (layer.getType() == MapLayerInfo.TYPE_REMOTE_VECTOR) {
                combinedList[i] = userRequestedFilter;
            } else if (layer.getType() == MapLayerInfo.TYPE_VECTOR) {
                layerDefinitionFilter = layer.getFeature().getFilter();

                // heck, how I wish we use the null objects more
                if (layerDefinitionFilter == null) {
                    layerDefinitionFilter = Filter.INCLUDE;
                }
                combined = filterFactory.and(layerDefinitionFilter, userRequestedFilter);
                //combined = filterFac.and(combined, OrImpl.);
                FeatureTypeConstraint[] featureTypeConstraints = layer.getLayerFeatureConstraints();
                if (featureTypeConstraints != null) {
                    List<Filter> filters = new ArrayList<Filter>();
                    for (int j = 0; j < featureTypeConstraints.length; j++) {
                        FeatureTypeConstraint featureTypeConstraint = featureTypeConstraints[j];
                        filters.add(featureTypeConstraint.getFilter());
                    }
                    combined = filterFactory.and(combined, filterFactory.and(filters));
                }
                combinedList[i] = combined;
            }
        }
        return combinedList;
    }
    
    private WebMap buildErrorImage(GetMapRequest request, WMSMapContext mapContext, Exception e) {
		String message = e.getMessage();
		if(message == null){
			message = "Acid Map Server Error";
		}
		BufferedImage errorImage = errorImageFactory.getErrorImage(request.getWidth(), request.getHeight(), message);
		return buildRendererImageMap(errorImage, request.getFormat(), mapContext);
	}
	
	private WebMap buildRendererImageMap(BufferedImage image, String format, WMSMapContext mapContext){
		final String outputFormat = format;
		RenderedImageMap result = new RenderedImageMap(mapContext, image, outputFormat);
		return result;
	}
}
