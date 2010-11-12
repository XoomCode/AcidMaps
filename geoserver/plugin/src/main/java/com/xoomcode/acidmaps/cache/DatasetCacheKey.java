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
	 * @see java.lang.Object#hashCode()
	 */
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((layer == null) ? 0 : layer.hashCode());
		return result;
	}

	/* (non-Javadoc)
	 * @see java.lang.Object#equals(java.lang.Object)
	 */
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		DatasetCacheKey other = (DatasetCacheKey) obj;
		if (layer == null) {
			if (other.layer != null)
				return false;
		} else if (!layer.equals(other.layer))
			return false;
		return true;
	}
	
}
