package com.xoomcode.acidmaps.adapter;

import com.xoomcode.acidmaps.Configuration;

public class JCAdapter {
	
	private native void interpolateC(Configuration configuration, byte[] out);
	
	static {
		// The runtime system executes a class's static
		// initializer when it loads the class.
		System.loadLibrary("AcidMapsJCAdapter");
	}
	
	public void interpolate(byte[] out){
		interpolateC(new Configuration(), out);
	}
}
