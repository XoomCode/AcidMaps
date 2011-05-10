package com.xoomcode.acidmaps.error;

import com.xoomcode.acidmaps.core.Configuration;

public class Validator {

	public static int validate(Configuration cfg) {
		if(cfg.dataset == null || cfg.dataset.length == 0) return 1;
		if(cfg.datasetSize < 0) return 2;
		if(cfg.simplifyMethod < 0 || cfg.simplifyMethod > 3) return 3;	
		if(cfg.simplifySize < 0) return 4;
		if(cfg.bounds == null) return 5;
		if(cfg.interpolationStrategy < 0 || cfg.interpolationStrategy > 3) return 6;
		if(cfg.radius < 0) return 7;
		if(cfg.width < 0 || cfg.height < 0) return 8;
		if(cfg.intervals == null || cfg.intervals.length == 0) return 9;
		if(cfg.intervalsColors == null || cfg.intervalsColors.length == 0) return 10;
		if(cfg.rendererType < 0 || cfg.rendererType > 3) return 12;
		if(cfg.format < 0 || cfg.format > 0) return 13;
		for(int i = 0; i < cfg.intervals.length - 1; i++){
			if(cfg.intervals[i] >= cfg.intervals[i + 1]) return 14;
		}
		return 0;
	}

}
