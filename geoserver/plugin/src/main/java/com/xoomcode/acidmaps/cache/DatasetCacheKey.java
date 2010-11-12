/**
 * 
 */
package com.xoomcode.acidmaps.cache;


/**
 * @date 11/11/2010
 * @author cfarina
 *	
 */
public class DatasetCacheKey {

	private String layer;
	
	/**
	 * @param layer
	 */
	public DatasetCacheKey(String layer) {
		super();
		this.layer = layer;
	}

	/**
	 * @return the layer
	 */
	public String getLayer() {
		return layer;
	}

	/**
	 * @param layer the layer to set
	 */
	public void setLayer(String layer) {
		this.layer = layer;
	}

	/* (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		return super.equals(obj);
	}
	
	
}
