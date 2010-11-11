package com.xoomcode.acidmaps.core;

// TODO: Auto-generated Javadoc
/**
 * Bounding Box representation Instances of this class represent bounding
 * boxes. Data stored as left, bottom, right, top floats. All values are
 * initialized to 0, however, you should make sure you set them before
 * using the bounds for anything.
 */
public class Bounds {

	/** The min x. */
	public float minX;
	
	/** The min y. */
	public float minY;
	
	/** The max x. */
	public float maxX;
	
	/** The max y. */
	public float maxY;

	public Bounds() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param minX
	 * @param minY
	 * @param maxX
	 * @param maxY
	 */
	public Bounds(float minX, float minY, float maxX, float maxY) {
		super();
		this.minX = minX;
		this.minY = minY;
		this.maxX = maxX;
		this.maxY = maxY;
	}
	
	
	
}
