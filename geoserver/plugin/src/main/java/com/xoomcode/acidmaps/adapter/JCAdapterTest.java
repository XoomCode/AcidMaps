package com.xoomcode.acidmaps.adapter;

public class JCAdapterTest {

	public static void main(String[] args) {
		JCAdapter jCAdapter = new JCAdapter();
		
		byte[] out = new byte[5];
		
		jCAdapter.interpolate(out);
		
		for (byte c : out) {
			System.out.print(c);
		}
		
	}
}
