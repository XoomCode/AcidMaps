/**
 * @author cfarina
 * @date 15/03/2011
 * 
 * The Color class is used encapsulate colors in the default sRGB color space
 */

package com.xoomcode.acidmaps.core;

public class Color {

	public byte r;
	public byte g;
	public byte b;
	public byte a;
	
	/**
	 * Instantiates a new color.
	 *
	 * @param r the r
	 * @param g the g
	 * @param b the b
	 * @param a the a
	 */
	public Color(byte r, byte g, byte b, byte a) {
		super();
		this.r = r;
		this.g = g;
		this.b = b;
		this.a = a;
	}
	
}
