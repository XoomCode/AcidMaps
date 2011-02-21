/*
 * 
 */
package com.xoomcode.acidmaps;

import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;

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
import com.xoomcode.acidmaps.constants.Constants;
import com.xoomcode.acidmaps.core.AcidMapParameters;
import com.xoomcode.acidmaps.core.Bounds;
import com.xoomcode.acidmaps.core.Configuration;

// TODO: Auto-generated Javadoc
/**
 * The Class AcidMapService.
 */
public class AcidMapService {
	
	private static DatasetCache datasetCache = new DatasetCache();
	
	/** The filter fac. */
	private FilterFactory filterFac;
	
	/** The Constant RGBA_SIZE. */
	public static final int RGBA_SIZE = 4;

	/**
	 * Instantiates a new acid map service.
	 */
	public AcidMapService() {
		this.filterFac = CommonFactoryFinder.getFilterFactory(GeoTools.getDefaultHints());
	}
	
	/**
	 * Sets the filter factory.
	 *
	 * @param filterFactory the new filter factory
	 */
	public void setFilterFactory(final FilterFactory filterFactory) {
        this.filterFac = filterFactory;
    }

	/**
	 * Gets the map.
	 *
	 * @param request the request
	 * @return the web map
	 * @throws ServletException the servlet exception
	 * @throws IOException Signals that an I/O exception has occurred.
	 */
	public WebMap GetMap(GetMapRequest request) throws ServletException,
			IOException {
		WMSMapContext mapContext = new WMSMapContext(request);
		try {
			if (request.getLayers() != null && request.getLayers().size() > 0) {
				MapLayerInfo layer = request.getLayers().get(0);
				DatasetCacheKey datasetCacheKey = new DatasetCacheKey(layer.getName(), request.getFilter().toString());
				if(datasetCache.isCached(datasetCacheKey)){
					return run(request, mapContext);
				} else {
					return synchronizedRun(request, mapContext);
					
				}
			}
			return null;
		} catch (ServiceException e) {
			mapContext.dispose();
			throw e;
		} catch (RuntimeException e) {
			mapContext.dispose();
			throw (RuntimeException) e;
		} catch (Exception e) {
			mapContext.dispose();
			throw new ServiceException("Internal error ", e);
		}
	}

	/**
	 * Run.
	 *
	 * @param request the request
	 * @param mapContext the map context
	 * @return the web map
	 * @throws ServiceException the service exception
	 * @throws IOException Signals that an I/O exception has occurred.
	 */
	
	public synchronized WebMap synchronizedRun(final GetMapRequest request, WMSMapContext mapContext) throws ServiceException, IOException {
		Map<String, String> rawKvp = request.getRawKvp();
		String valueColumn = rawKvp.get(AcidMapParameters.VALUE_COLUMN);
		
		MapLayerInfo layer = request.getLayers().get(0);
		DatasetCacheKey datasetCacheKey = new DatasetCacheKey(layer.getName(), request.getFilter().toString());
		
		Filter layerFilter = buildLayersFilters(request.getFilter(), request.getLayers())[0];
		//Style layerStyle = request.getStyles().toArray(new Style[] {})[0];
		
		FeatureSource<? extends FeatureType, ? extends Feature> source = layer.getFeatureSource(true);
		FeatureType schema = source.getSchema();
		final GeometryDescriptor geometryAttribute = schema.getGeometryDescriptor();
		
		float[] dataset = null;
		if(!datasetCache.isCached(datasetCacheKey)){
			FeatureCollection<? extends FeatureType, ? extends Feature> features = source.getFeatures(layerFilter);
			FeatureIterator<? extends Feature> featureIterator = features.features();
			dataset = new float[features.size() * 3];
			int i = 0;
			while (featureIterator.hasNext()) {
				SimpleFeature f = (SimpleFeature) featureIterator.next();
				Property theGeom = f.getProperty(geometryAttribute.getName());
				Point point = (Point)theGeom.getValue();
				dataset[i] = (float)point.getX();
				dataset[i+1] = (float)point.getY();
				
				Property value = f.getProperty(valueColumn);
				if(value != null){
					dataset[i+2] = new Float((Double)value.getValue());
				}
				i+=3;
			}
			datasetCache.put(datasetCacheKey, dataset);
		}
		return run(request, mapContext);
	}

	public WebMap run(final GetMapRequest request, WMSMapContext mapContext)
			throws ServiceException, IOException {

		Configuration configuration = buildConfiguration(request);
		
		MapLayerInfo layer = request.getLayers().get(0);
		
		DatasetCacheKey datasetCacheKey = new DatasetCacheKey(layer.getName(), request.getFilter().toString());
		
		configuration.dataset = datasetCache.getDataset(datasetCacheKey);;
		
		JCAdapter jCAdapter = new JCAdapter();
		byte[] outputBuffer = jCAdapter.interpolate(configuration);
		
		BufferedImage image=ImageIO.read(new ByteArrayInputStream(outputBuffer));
		//File input = new File("/home/cfarina/wk/geoserver/acidmaps/src/main/java/com/xoomcode/acidmaps/landscape.png");
		//BufferedImage image = ImageIO.read(input);
		
        final String outputFormat = request.getFormat();
        RenderedImageMap result = new RenderedImageMap(mapContext, image, outputFormat);
        return result;
		
	}
	
	/**
	 * @param request
	 * @param rawKvp
	 * @return
	 */
	private Configuration buildConfiguration(final GetMapRequest request) {
		Map<String, String> rawKvp = request.getRawKvp();
		int simplifyMethod = new Integer(rawKvp.get(AcidMapParameters.SIMPLIFY_METHOD));
		int simplifySize = new Integer(rawKvp.get(AcidMapParameters.SIMPLIFY_SIZE));
		int[] intervals = buildIntervals(rawKvp.get(AcidMapParameters.INTERVALS));
		byte[] intervalsColors = buildIntervalsColors(rawKvp.get(AcidMapParameters.INTERVALS_COLORS));
		int intervalsType = new Integer(rawKvp.get(AcidMapParameters.INTERVALS_TYPE));
		int interpolationStrategy = new Integer(rawKvp.get(AcidMapParameters.INTERPOLATION_STRATEGY));
		int interpolationParameter = new Integer(rawKvp.get(AcidMapParameters.INTERPOLATION_PARAMETER));
		
		Configuration configuration = new Configuration();
		configuration.simplifyMethod = simplifyMethod;
		configuration.simplifySize = simplifySize;

		Bounds bounds = new Bounds();
		bounds.minY = (float)request.getBbox().getMinY();
		bounds.minX = (float)request.getBbox().getMinX();
		bounds.maxY = (float)request.getBbox().getMaxY();
		bounds.maxX = (float)request.getBbox().getMaxX();
		configuration.bounds = bounds;
		
		configuration.width = request.getWidth();
		configuration.height = request.getHeight();
		
		configuration.intervals = intervals;
		configuration.intervalsColors = intervalsColors;
		configuration.intervalsType = intervalsType;
		configuration.interpolationStrategy = interpolationStrategy;
		configuration.interpolationParameter = interpolationParameter;
		return configuration;
	}
	
	/**
	 * @param string
	 * @return
	 */
	private byte[] buildIntervalsColors(String intervalsColorStr) {
		String[] split = intervalsColorStr.split(",");
		
		byte [] intervalsColor = new byte[split.length];	
		
		for (int i = 0; i < intervalsColor.length; i++) {
			intervalsColor[i] = (byte)(int)new Integer(split[i]);
		}
		return intervalsColor;
	}

	/**
	 * @param string
	 * @return
	 */
	private int[] buildIntervals(String intervalsStr) {
		String[] split = intervalsStr.split(",");
		
		int	[] intervals = new int[split.length];	
		
		for (int i = 0; i < intervals.length; i++) {
			intervals[i] = new Integer(split[i]);
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
                combined = filterFac.and(layerDefinitionFilter, userRequestedFilter);

                FeatureTypeConstraint[] featureTypeConstraints = layer.getLayerFeatureConstraints();
                if (featureTypeConstraints != null) {
                    List<Filter> filters = new ArrayList<Filter>();
                    for (int j = 0; j < featureTypeConstraints.length; j++) {
                        FeatureTypeConstraint featureTypeConstraint = featureTypeConstraints[j];
                        filters.add(featureTypeConstraint.getFilter());
                    }
                    combined = filterFac.and(combined, filterFac.and(filters));
                }
                combinedList[i] = combined;
            }
        }
        return combinedList;
    }
}
