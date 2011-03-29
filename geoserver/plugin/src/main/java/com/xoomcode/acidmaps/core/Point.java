/**
 * 
 */
package com.xoomcode.acidmaps.core;

// TODO: Auto-generated Javadoc
/**
 * A point representing a location in (x, y) coordinate space, 
 * and a value for that point.
 *
 * @date 22/02/2011
 * @author cfarina
 */
public class Point {
	
	/** The x. */
	public float x;
	
	/** The y. */
	public float y;
	
	/** The value. */
	public float value;

	/**
	 * Instantiates a new point.
	 */
	public Point() {
	}
	
	/**
	 * Instantiates a new point.
	 *
	 * @param x the x
	 * @param y the y
	 * @param value the value
	 */
	public Point(float x, float y, float value) {
		this.x = x;
		this.y = y;
		this.value = value;
	}
	
}
