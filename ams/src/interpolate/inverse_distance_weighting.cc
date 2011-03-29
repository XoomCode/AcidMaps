/**
 * @file inverse_distance_weighting.cc
 * @brief Inverse Distance Weighted Interpolation
 *
 * @date 2011-01-05
  
 * @authors Fabio R. Panettieri
 */

#include "./inverse_distance_weighting.h"

#include <cstring>
#include <cmath>

#include "../constants/constants.h"
#include "../core/size.h"
#include "../core/pixel.h"
#include "../core/rectangle.h"

namespace acid_maps {

/**
 * @todo
 */
void InverseDistanceWeighting::interpolate(Size* tile_size, Pixel* dataset, int dataset_size,
  int radius, float interpolated_bitmap[]) {
  Pixel* pixel;
  float distance_x, distance_y, weight, accummulated_value, accummulated_weight;
  for (int y = 0; y < tile_size->height; y++) {
    for (int x = 0; x < tile_size->width; x++) {
      accummulated_value = 0;
      accummulated_weight = 0;
      for (int i = 0; i < dataset_size; i++) {
        pixel = dataset + i;
        distance_x = static_cast<float>(x - pixel->x);
        distance_y = static_cast<float>(y - pixel->y);
        if (distance_x == 0 && distance_y == 0) {
          weight = 1.0f;
        } else {
          weight = 1.0f / (std::pow(distance_x, 2.0f) + std::pow(distance_y, 2.0f));
        }
        accummulated_value += pixel->value  * weight;
        accummulated_weight += weight;
      }
      interpolated_bitmap[y * tile_size->width + x] = accummulated_value / accummulated_weight;
    }
  }
}

};  // namespace acid_maps

