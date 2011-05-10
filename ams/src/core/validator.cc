/**
 * @file validator.cc
 * @brief Validates the configuration
 *
 * @date 2011-03-04
 * @authors Fabio R. Panettieri
 */

#include "./validator.h"
#include "./configuration.h"

#include <cstddef>

namespace acid_maps {

int Validator::validate(Configuration* cfg) {
	
	if(cfg->dataset == NULL) return 1;
	if(cfg->dataset_size < 0) return 2;
	if(cfg->simplify_method < 0 || cfg->simplify_method > 3) return 3;	
	if(cfg->simplify_size < 0) return 4;
	if(cfg->bounds == NULL) return 5;
	if(cfg->interpolation_strategy < 0 || cfg->interpolation_strategy > 3) return 6;
	if(cfg->radius < 0) return 7;
	if(cfg->tile_size == NULL) return 8;
	if(cfg->intervals == NULL) return 9;
	if(cfg->intervals_colors == NULL) return 10;
	if(cfg->intervals_size <= 0) return 11;
	if(cfg->renderer_type < 0 || cfg->renderer_type > 3) return 12;
	if(cfg->format < 0 || cfg->format > 0) return 13;
	for(int i = 0; i < cfg->intervals_size - 1; i++){
		if(cfg->intervals[i] >= cfg->intervals[i + 1]) return 14;
	}
	
	return 0;
}

};  // namespace acid_maps

