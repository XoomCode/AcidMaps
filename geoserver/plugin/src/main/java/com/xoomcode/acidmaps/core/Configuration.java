package com.xoomcode.acidmaps.core;

// TODO: Auto-generated Javadoc
/**
 * @date 09/11/2010
 * @author cfarina
 * The Class Configuration.
 */
public class Configuration {

	/** Set of valued points, stored 3 floats per point. X, Y, Value */
	public Point[] dataset;
	
	public int datasetSize;

	/** Desired simplify method. */
	public int simplifyMethod;

	/** Size of the simplified sample. */
	public int simplifySize;

	/** Requested tile bounds. */
	public Bounds bounds;

	/** Strategy used to interpolate missing values. */
	public int interpolationStrategy;

	/** Output image width. */
	public int width;

	/** Output image height. */
	public int height;

	/** Interpolation parameter for every interpolation type. */
	public int interpolationParameter;
	
	public float[] intervals;
	
	public byte[] intervalsColors;
	
	public int intervalsSize;
	
	public int rendererType;
	
	public int format;

	/**
	 * Instantiates a new configuration.
	 */
	public Configuration() {
	}
}
