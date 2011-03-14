package com.xoomcode.acidmaps.adapter;

import com.xoomcode.acidmaps.constants.ErrorConstants;
import com.xoomcode.acidmaps.core.Configuration;
import com.xoomcode.acidmaps.error.AcidMapException;

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
	 * @throws AcidMapException 
	 */
	public byte[] interpolate(Configuration configuration) throws AcidMapException{
		Object interpolateC = interpolateC(configuration);

		if(interpolateC == null){
			throw new AcidMapException("Error in acidMapsLibrary. Code: " + ErrorConstants.getErrorString(configuration.error));
		}
		
		if(interpolateC instanceof byte[]){
			return (byte[])interpolateC;
		} 
		return null;
	}
}
