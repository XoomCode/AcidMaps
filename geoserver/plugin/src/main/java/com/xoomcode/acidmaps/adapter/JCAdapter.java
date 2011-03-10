package com.xoomcode.acidmaps.adapter;

import com.xoomcode.acidmaps.core.Configuration;

// TODO: Auto-generated Javadoc
/**
 * The Class JCAdapter.
 * @date 09/11/2010
 * @author cfarina
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
	private native Object interpolateC(Configuration configuration);
	
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
		Object interpolateC = interpolateC(configuration);
		if(interpolateC instanceof byte[]){
			return (byte[])interpolateC;
		} 
		return null;
	}
}
