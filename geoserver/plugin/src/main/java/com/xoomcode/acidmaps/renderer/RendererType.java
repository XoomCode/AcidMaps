/**
 * 
 */
package com.xoomcode.acidmaps.renderer;

/**
 * @date 09/11/2010
 * @author cfarina
 *	
 * List of available rendere types
 */
public class RendererType {

	public static final int DENSE = 0;             // Intervals are indexed
	public static final int SPARSE = 1;            // Finds the right interval with a b-tree
	public static final int GRADIENT = 2;            // Smooth color rendering
}
