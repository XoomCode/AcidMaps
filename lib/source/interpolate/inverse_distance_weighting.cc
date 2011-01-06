/**
 * @file inverse_distance_weighting.cc
 * @brief Inverse Distance Weighted Interpolation
 *
 * @date 2011-01-05
  
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/size.h"
#include "../core/rectangle.h"
#include "./inverse_distance_weighting.h"
#include <cstring>
#include <cmath>

namespace acid_maps {

/**
 * @todo
 */
void InverseDistanceWeighting::interpolate(Size* tile_size, int dataset[], int dataset_size, 
  int radius, int interpolated_bitmap[]) {

	float distance_x, distance_y, distance, weight, accummulated_value, accummulated_weight;
  for (int y = 0; y < tile_size->height; y++) {
    for (int x = 0; x < tile_size->width; x++) {  
    
    	accummulated_value = 0;
    	accummulated_weight = 0;
		  for (int i = 0; i < dataset_size; i++) {
        distance_x = x - dataset[VPP * i];
        distance_y = y - dataset[VPP * i + 1];
        
        if(distance_x == 0 && distance_y == 0){
        	weight = 1;
        } else {
        	weight = 1.0 / (std::pow(distance_x, 2) + std::pow(distance_y, 2));
        }
        
        accummulated_value += dataset[VPP * i + 2]  * weight;
        accummulated_weight += weight;
      }
	    interpolated_bitmap[y * tile_size->width + x] = accummulated_value / accummulated_weight;
    }
  }

}

};  // namespace acid_maps

