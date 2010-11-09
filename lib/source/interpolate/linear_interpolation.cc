/**
 * @file linear_interpolation.cc
 * @brief Linear interpolation implementation
 *
 * @date 2010-11-09
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/size.h"
#include "../core/rectangle.h"
#include "./linear_interpolation.h"
#include <cstring>
#include <cmath>

namespace acid_maps {

/**
 * @todo REFACTOR THIS IN MULTIPLE FUNCTIONS
 */
void LinearInterpolation::interpolate(Size* tile_size, int dataset[], int dataset_size, 
  int radius, int interpolated_bitmap[]) {
  std::memset(interpolated_bitmap, 0, dataset_size * sizeof(interpolated_bitmap[0]));
  
  Rectangle bounds;
  int point_x, point_y, point_value;
  int distance_x, distance_y, distance;
  for (int i = 0; i < dataset_size; i++) {
    point_x = dataset[VPP * i];
    point_y = dataset[VPP * i + 1];
    point_value = dataset[VPP * i + 2];
    
    bounds.resize(0, 0, tile_size->width, tile_size->height);
    bounds.intersect(point_x - radius, point_x + radius, point_y - radius, point_y + radius);
    
    for (int y = bounds.min_y; y < bounds.max_y; y++) {
      for (int x = bounds.min_x; x < bounds.max_x; x++) {
        distance_x = x - point_x;
        distance_y = y - point_y;
        distance = std::sqrt(std::pow(distance_x, 2) + std::pow(distance_y, 2));
        
        if (distance < radius) {
          interpolated_bitmap[y * tile_size->width + x] += point_value * (1 - distance / radius);
        }
      }
    }
    
  }
}

};  // namespace acid_maps

