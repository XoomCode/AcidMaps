/**
 * @file linear_interpolation.cc
 * @brief Linear interpolation implementation
 *
 * @date 2010-11-09
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/size.h"
#include "../core/pixel.h"
#include "../core/rectangle.h"
#include "./linear_interpolation.h"
#include <cstring>
#include <cmath>

namespace acid_maps {

/**
 * @todo REFACTOR THIS IN MULTIPLE FUNCTIONS
 */
void LinearInterpolation::interpolate(Size* tile_size, Pixel* dataset, int dataset_size, 
  int radius, float interpolated_bitmap[]) {
  std::memset(interpolated_bitmap, 0, tile_size->width * tile_size->height * sizeof(interpolated_bitmap[0]));
  
  Rectangle bounds;
  Pixel* pixel;
  float distance_x, distance_y, distance;
  for (int i = 0; i < dataset_size; i++) {
    pixel = dataset + i;
    
    bounds.resize(0, 0, tile_size->width, tile_size->height);
    bounds.intersect(pixel->x - radius, pixel->y - radius, pixel->x + radius, pixel->y + radius);
    
    for (int y = bounds.min_y; y < bounds.max_y; y++) {
      for (int x = bounds.min_x; x < bounds.max_x; x++) {
        distance_x = x - pixel->x;
        distance_y = y - pixel->y;
        distance = std::sqrt(std::pow(distance_x, 2) + std::pow(distance_y, 2));
        
        if (distance < radius) {
          interpolated_bitmap[y * tile_size->width + x] += pixel->value * (1 - distance / radius);
        }
      }
    }
    
    
  }
}

};  // namespace acid_maps

