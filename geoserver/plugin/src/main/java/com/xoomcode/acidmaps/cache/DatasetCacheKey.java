/**
 * 
 */
package com.xoomcode.acidmaps.cache;


/**
 * @date 11/11/2010
 * @author cfarina
 *
 * Every cached data is identify by an unique key. This key is
 * formed by the layer name and the CQLFilter.
 */
public class DatasetCacheKey {

	private String layer;
	
	private String filter;
	
	private int filterHash;
	
	/**
	 * @param layer
	 */
	public DatasetCacheKey(String layer, String filter) {
		super();
		this.layer = layer;
		this.filter = filter;
		filterHash = filter.hashCode();
	}

	/**
	 * @return the filter
	 */
	public String getFilter() {
		return filter;
	}
	
	/**
	 * @param filter the filter to set
	 */
	public void setFilter(String filter) {
		this.filter = filter;
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
		result = prime * result + filterHash;
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
		if (filterHash != other.filterHash)
			return false;
		if (layer == null) {
			if (other.layer != null)
				return false;
		} else if (!layer.equals(other.layer))
			return false;
		return true;
	}
	
}
