/**
 * @file nearest_neighbor.cc
 * @brief Nearest Neighbor interpolation implementation
 *
 * @date 2010-11-09
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/size.h"
#include "./nearest_neighbor.h"
#include <cstring>
#include <climits>
#include <cmath>

namespace acid_maps {

/**
 * @todo use the parameter
 * @todo marching squares
 */
void NearestNeighbor::interpolate(Size* tile_size, int dataset[], int dataset_size, 
  int interpolation_parameter, int interpolated_bitmap[]) {
  
  int value;
  int minimum_distance;
  
  int distance_x, distance_y, distance;
  for (int x = 0; x < tile_size->width; x++) {
    for (int y = 0; y < tile_size->height; y++) {
      
      int min_distance = INT_MAX;
      for (int i = 0; i < dataset_size; i++) {
        distance_x = x - dataset[VPP * i];
        distance_y = y - dataset[VPP * i + 1];
        distance = std::sqrt(std::pow(distance_x, 2) + std::pow(distance_y, 2));
        
        if (distance <  minimum_distance) {
          minimum_distance = distance;
          value = dataset[VPP * i + 2];      
        }  
      }
      interpolated_bitmap[y * tile_size->width + x] = value;
    
    }
  }
  
}

};  // namespace acid_maps
