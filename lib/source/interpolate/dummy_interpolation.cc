/**
 * @file dummy_interpolation.cc
 * @brief Dummy interpolation implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/size.h"
#include "../core/pixel.h"
#include "./dummy_interpolation.h"
#include <cstring>

namespace acid_maps {

/**
 * @todo use the parameter
 */
void DummyInterpolation::interpolate(Size* tile_size, Pixel* dataset, int dataset_size, 
  int interpolation_parameter, float interpolated_bitmap[]) {
  std::memset(interpolated_bitmap, 0, dataset_size * sizeof(interpolated_bitmap[0]));
  
  Pixel* pixel;
  for (int i = 0; i < dataset_size; i++) {
    pixel = dataset + i;
    
    if (pixel->x >= 0 && pixel->x < tile_size->width && pixel->y >= 0 && pixel->y < tile_size->height) {
      interpolated_bitmap[pixel->y * tile_size->width + pixel->x] = pixel->value;
    }
  }
}

};  // namespace acid_maps

