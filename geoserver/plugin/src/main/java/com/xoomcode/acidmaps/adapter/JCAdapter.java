package com.xoomcode.acidmaps.adapter;

import com.xoomcode.acidmaps.core.Configuration;

// TODO: Auto-generated Javadoc
/**
 * The Class JCAdapter.
 */
public class JCAdapter {
	
	/**
	 * 
	 */
	public JCAdapter() {
		// TODO Auto-generated constructor stub
	}
	
	/**
	 * Interpolate c.
	 *
	 * @param configuration the configuration
	 * @param out the out
	 */
	private native byte[] interpolateC(Configuration configuration);
	
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
	public byte[] interpolate(Configuration configuration){
		return interpolateC(configuration);
	}
}
