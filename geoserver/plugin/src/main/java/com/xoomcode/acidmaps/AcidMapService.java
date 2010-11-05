package com.xoomcode.acidmaps;

import java.awt.image.BufferedImage;
import java.awt.image.RenderedImage;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import javax.imageio.ImageIO;
import javax.media.jai.JAI;
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
import org.geotools.styling.Style;
import org.opengis.feature.Feature;
import org.opengis.feature.simple.SimpleFeature;
import org.opengis.feature.type.FeatureType;
import org.opengis.filter.Filter;
import org.opengis.filter.FilterFactory;

import com.vividsolutions.jts.geom.Envelope;
import com.xoomcode.acidmaps.adapter.JCAdapter;
import com.xoomcode.acidmaps.core.Bounds;
import com.xoomcode.acidmaps.core.Configuration;

public class AcidMapService {
	
	private FilterFactory filterFac;
	
	public static final int RGBA_SIZE = 4;

	public AcidMapService() {
		this.filterFac = CommonFactoryFinder.getFilterFactory(GeoTools.getDefaultHints());
	}
	
	public void setFilterFactory(final FilterFactory filterFactory) {
        this.filterFac = filterFactory;
    }

	public WebMap GetMap(GetMapRequest request) throws ServletException,
			IOException {
		WMSMapContext mapContext = new WMSMapContext(request);
		try {
			if (request.getLayers() != null && request.getLayers().size() > 0) {
				return run(request, mapContext);
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

	public WebMap run(final GetMapRequest request, WMSMapContext mapContext)
			throws ServiceException, IOException {
		final Envelope envelope = request.getBbox();
		final String featureVersion = request.getFeatureVersion();

		MapLayerInfo layer = null;
		
		layer = request.getLayers().get(0);
		Filter layerFilter = buildLayersFilters(request.getFilter(), request.getLayers())[0];
		Style layerStyle = request.getStyles().toArray(new Style[] {})[0];
		
		FeatureSource<? extends FeatureType, ? extends Feature> source = layer.getFeatureSource(true);
		FeatureType type = source.getSchema();
		String geometry = type.getGeometryDescriptor().getName().getLocalPart();

        ArrayList<Object> points = new ArrayList<Object>();
		FeatureCollection<? extends FeatureType, ? extends Feature> features = source.getFeatures(layerFilter);
		FeatureIterator<? extends Feature> featureIterator = features.features();
		while (featureIterator.hasNext()) {
			SimpleFeature f = (SimpleFeature) featureIterator.next();
			Object x = f.getAttribute("x");
			Object y = f.getAttribute("y");
			points.add(new Object[] { x, y });
		}
		//TODO: Asignar puntos
		
		Configuration configuration = new Configuration();
		configuration.width = request.getWidth();
		configuration.height = request.getHeight();
		Bounds bounds = new Bounds();
		
		//TODO: Revisar si esto esta bien
		bounds.minY = (float)request.getBbox().getMinY();
		bounds.maxY = (float)request.getBbox().getMaxY();
		bounds.minY = (float)request.getBbox().getMinX();
		bounds.maxX = (float)request.getBbox().getMaxX();
		configuration.bounds = bounds;
		
		byte[] out = new byte[configuration.width * configuration.height * RGBA_SIZE];
		JCAdapter jCAdapter = new JCAdapter();
		jCAdapter.interpolate(new Configuration(), out);
		
		BufferedImage image=ImageIO.read(new ByteArrayInputStream(out));
		RenderedImage renderedImage = JAI.create("fileload", image);
        final String outputFormat = request.getFormat();
        RenderedImageMap result = new RenderedImageMap(mapContext, renderedImage, outputFormat);
        return result;
		
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
