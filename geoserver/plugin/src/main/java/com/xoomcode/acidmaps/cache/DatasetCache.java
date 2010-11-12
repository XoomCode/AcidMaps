/**
 * 
 */
package com.xoomcode.acidmaps.cache;

import java.util.HashMap;
import java.util.Hashtable;
import java.util.Map;

/**
 * @date 11/11/2010
 * @author cfarina
 *	
 */
public class DatasetCache {

	private Map<DatasetCacheKey, Dataset> cache = new Hashtable<DatasetCacheKey, Dataset>();

	/**
	 * @param datasetCacheKey
	 * @return
	 */
	public boolean isCached(DatasetCacheKey datasetCacheKey) {
		return cache.get(datasetCacheKey) != null;
	}

	/**
	 * @param datasetCacheKey
	 */
	public float[] getDataset(DatasetCacheKey datasetCacheKey) {
		return cache.get(datasetCacheKey).getDataset();
	}

	/**
	 * @param datasetCacheKey
	 * @param dataset
	 */
	public void put(DatasetCacheKey datasetCacheKey, float[] dataset) {
		Dataset cachedDataset = new Dataset(dataset, this, datasetCacheKey);
		cache.put(datasetCacheKey, cachedDataset);
		cachedDataset.initInvalidateTimer(10000);
	}

	/**
	 * @param dataset
	 */
	public void remove(Dataset dataset) {
		cache.remove(dataset.getDatasetCacheKey());
	}
	
	
}
