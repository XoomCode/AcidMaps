package com.xoomcode.acidmaps.interpolate
{
	public class InterpolationStrategy
	{
		public static const DUMMY:int = 0;                       // No interpolation uses the assigned value
		public static const NEAREST_NEIGHBOR:int = 1;            // N Neighbors found
		public static const LINEAR:int = 2;                      // Value decays with distance
		public static const INVERSE_DISTANCE_WEIGHTING:int = 3;  // Simple implementation of IDW

	}
}