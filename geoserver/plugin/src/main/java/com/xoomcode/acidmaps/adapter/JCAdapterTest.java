package com.xoomcode.acidmaps.adapter;

import com.xoomcode.acidmaps.core.Configuration;

// TODO: Auto-generated Javadoc
/**
 * The Class JCAdapterTest.
 */
public class JCAdapterTest {

	/**
	 * The main method.
	 *
	 * @param args the arguments
	 */
	public static void main(String[] args) {
		JCAdapter jCAdapter = new JCAdapter();
		
		byte[] out = new byte[5];
		
		jCAdapter.interpolate(new Configuration(), out);
		
		for (byte c : out) {
			System.out.print(c);
		}
		
	}
}
