package com.xoomcode.acidmaps.core;

// TODO: Auto-generated Javadoc
/**
 * The Class Configuration.
 */
public class Configuration {

	/** Set of valued points, stored 3 floats per point. X, Y, Value */
	public float[] dataset;

	/** Number of points in the dataset. */
	/** @note Each point is composed of 3 floats, X, Y, Value */
	public int datasetSize;

	/** Desired simplify method. */
	public int simplifyMethod;

	/** Size of the simplified sample. */
	public int simplifySize;

	/** Requested tile bounds. */
	public Bounds bounds;

	/** Strategy used to interpolate missing values. */
	public int interpolationStrategy;

	/** Interpolated values will be stored here. */
	public int[] interpolatedBitmap;

	/** Output image width. */
	public int width;

	/** Output image height. */
	public int height;

	/** Bits per pixel. Allowed values are 24(RGB) or 32(RGBA) */
	public int colorDepth;

	/** Interpolation parameter for every interpolation type. */
	public int interpolationParameter;
	
	public int[] intervals;
	
	public int[] intervalColors;
	
	public int intervalSize;

	/**
	 * Instantiates a new configuration.
	 */
	public Configuration() {
	}
}
