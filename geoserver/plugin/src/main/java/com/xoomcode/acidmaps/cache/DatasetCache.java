/**
 * 
 */
package com.xoomcode.acidmaps.cache;

import java.util.ArrayList;
import java.util.Date;
import java.util.Hashtable;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;

import com.xoomcode.acidmaps.core.Point;

/**
 * @date 11/11/2010
 * @author cfarina
 *	
 */
public class DatasetCache extends TimerTask {

	private Map<DatasetCacheKey, Dataset> cache = new Hashtable<DatasetCacheKey, Dataset>();

	private Timer timer = new Timer();
	
	public DatasetCache() {
		timer.scheduleAtFixedRate(this, 0, 60000);
	}
	
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
	public Point[] getDataset(DatasetCacheKey datasetCacheKey) {
		if(cache.get(datasetCacheKey) != null){
			//cache.get(datasetCacheKey).setDate(new Date());
			return cache.get(datasetCacheKey).getDataset();
		}
		return null;
	}

	/**
	 * @param datasetCacheKey
	 * @param dataset
	 */
	public void put(DatasetCacheKey datasetCacheKey, Point[] dataset) {
		Dataset cachedDataset = new Dataset(dataset);
		cache.put(datasetCacheKey, cachedDataset);
	}

	/* (non-Javadoc)
	 * @see java.util.TimerTask#run()
	 */
	@Override
	public void run() {
		List<DatasetCacheKey> datasetCacheKeyForRemove = new ArrayList<DatasetCacheKey>();
		Date now = new Date();
		for (DatasetCacheKey datasetCacheKey : cache.keySet()) {
			Dataset dataset = cache.get(datasetCacheKey);
			long delay = now.getTime() - dataset.getDate().getTime();
			if(delay > 10000){
				datasetCacheKeyForRemove.add(datasetCacheKey);
			}
		}
		
		for (DatasetCacheKey datasetCacheKey : datasetCacheKeyForRemove) {
			cache.remove(datasetCacheKey);
		}
		
	}
	
}
