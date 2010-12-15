/**
 * 
 */
package com.xoomcode.acidmaps.cache;

import java.util.Date;

/**
 * @date 11/11/2010
 * @author cfarina
 *	
 */
public class Dataset {

	private float[] dataset;
	
	private Date date = new Date();

	/**
	 * @param timer
	 * @param dataset
	 */
	public Dataset(float[] dataset) {
		this.dataset = dataset;
	}
	
	/**
	 * @param date the date to set
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
	public float[] getDataset() {
		return dataset;
	}

	/**
	 * @param dataset the dataset to set
	 */
	public void setDataset(float[] dataset) {
		this.dataset = dataset;
	}

}
