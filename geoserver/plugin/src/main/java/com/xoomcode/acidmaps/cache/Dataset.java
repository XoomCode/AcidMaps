/**
 * 
 */
package com.xoomcode.acidmaps.cache;

import java.util.Timer;
import java.util.TimerTask;

/**
 * @date 11/11/2010
 * @author cfarina
 *	
 */
public class Dataset extends TimerTask {

	private float[] dataset;
	
	private DatasetCacheKey datasetCacheKey;

	private DatasetCache datasetCache;
	
	/**
	 * @param timer
	 * @param dataset
	 */
	public Dataset(float[] dataset, DatasetCache datasetCache, DatasetCacheKey datasetCacheKey) {
		this.dataset = dataset;
		this.datasetCache = datasetCache;
		this.datasetCacheKey = datasetCacheKey;
	}
	
	public void initInvalidateTimer(int mils){
		
		Timer timer = new Timer(); 
		timer.scheduleAtFixedRate(this, 0, 1000);
	}
	
	/* (non-Javadoc)
	 * @see java.util.TimerTask#run()
	 */
	@Override
	public void run() {
		datasetCache.remove(this);
	}

	/**
	 * @return the datasetCache
	 */
	public DatasetCache getDatasetCache() {
		return datasetCache;
	}
	
	/**
	 * @param datasetCache the datasetCache to set
	 */
	public void setDatasetCache(DatasetCache datasetCache) {
		this.datasetCache = datasetCache;
	}
	
	/**
	 * @return the dataset
	 */
	public float[] getDataset() {
		return dataset;
	}

	/**
	 * @param dataset the dataset to set
	 */
	public void setDataset(float[] dataset) {
		this.dataset = dataset;
	}

	/**
	 * @return the datasetCacheKey
	 */
	public DatasetCacheKey getDatasetCacheKey() {
		return datasetCacheKey;
	}
	
	/**
	 * @param datasetCacheKey the datasetCacheKey to set
	 */
	public void setDatasetCacheKey(DatasetCacheKey datasetCacheKey) {
		this.datasetCacheKey = datasetCacheKey;
	}
}
