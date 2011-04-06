package com.xoomcode.acidmaps.constants;

import java.util.HashMap;
import java.util.Map;

public class ErrorConstants {
	
	public static Map<Integer, String> map = new HashMap<Integer, String>();
	
	static {
		map.put(1, "dataset is null.");
		map.put(2, "dataset size is 0.");
		map.put(3, "Simplify method is lower than 0 or greater than 3.");
		map.put(4, "Simplify size is lower than 0 or greater than dataset size.");
		map.put(5, "bounds is null.");
		map.put(6, "Interpolation strategy is lower than 0 or greater than 3.");
		map.put(7, "Radius is lower than 0.");
		map.put(8, "Tile size is null.");
		map.put(9, "Intervals is null.");
		map.put(10, "Intervals colors is null.");
		map.put(11, "Intervals size is null.");
		map.put(12, "Renderer type is lower than 1 or greater than 3.");
		map.put(13, "Format is lower than 0 or greater than 1.");
		map.put(14, "Malformed range.");
	}
	
	public static String getErrorString(Integer code){
		if(map.get(code) == null){
			return "Unknow error.";
		} else {
			return map.get(code);
		}
	}
}
