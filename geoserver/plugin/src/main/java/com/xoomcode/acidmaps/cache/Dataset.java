/**
 * 
 */
package com.xoomcode.acidmaps.cache;

import java.util.Date;

import com.xoomcode.acidmaps.core.Point;

/**
 * 
 * @date 11/11/2010
 * @author cfarina
 *	
 * It Saves the points cached by DatasetCache.
 */
public class Dataset {

	private Point[] dataset;
	
	private Date date = new Date();

	/**
	 * @param timer
	 * @param dataset
	 */
	public Dataset(Point[] dataset) {
		this.dataset = dataset;
	}
	
	/**
	 * @param date This property is used to invalidate
	 * the dataset when is cached.
	 */
	public void setDate(Date date) {
		this.date = date;
	}

	/**
	 * @return the date
	 */
	public Date getDate() {
		return date;
	}

	/**
	 * @return the dataset
	 */
	public Point[] getDataset() {
		return dataset;
	}

	/**
	 * @param dataset the dataset to set
	 */
	public void setDataset(Point[] dataset) {
		this.dataset = dataset;
	}

}
