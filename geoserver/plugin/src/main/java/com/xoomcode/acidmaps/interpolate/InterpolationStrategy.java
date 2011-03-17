package com.xoomcode.acidmaps.interpolate;

/**
 * @date 10/11/2010
 * @author cfarina
 * 
 * It defines the interpolate methods
 */
public class InterpolationStrategy {

	public static final int DUMMY = 0;                       // No interpolation uses the assigned value
	public static final int NEAREST_NEIGHBOR = 1;            // N Neighbors found
	public static final int LINEAR = 2;                      // Value decays with distance
	public static final int INVERSE_DISTANCE_WEIGHTING = 3;  // Simple implementation of IDW
}
