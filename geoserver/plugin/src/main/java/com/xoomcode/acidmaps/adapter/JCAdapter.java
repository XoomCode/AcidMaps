package com.xoomcode.acidmaps.adapter;

import com.xoomcode.acidmaps.core.Configuration;

// TODO: Auto-generated Javadoc
/**
 * The Class JCAdapter.
 */
public class JCAdapter {
	
	/**
	 * Interpolate c.
	 *
	 * @param configuration the configuration
	 * @param out the out
	 */
	private native void interpolateC(Configuration configuration, byte[] out);
	
	static {
		// The runtime system executes a class's static
		// initializer when it loads the class.
		System.loadLibrary("acid-maps-jni");
	}
	
	/**
	 * Interpolate.
	 *
	 * @param configuration the configuration
	 * @param out the out
	 */
	public void interpolate(Configuration configuration, byte[] out){
		interpolateC(configuration, out);
	}
}
