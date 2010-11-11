/**
 * @file transformer.cc
 * @brief Transformer implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/bounds.h"
#include "../core/configuration.h"
#include "./transformer.h"

namespace acid_maps {

/**
 * @ todo Store pixel positions in int*
 */
void Transformer::transform(Bounds* bounds, Size* tile_size, float dataset[],
  int dataset_size, int transformed_dataset[]) {

  float bounds_width = bounds->max_x - bounds->min_x;
  float bounds_height = bounds->max_y - bounds->min_y;

  float horizontal_resolution = bounds_width / tile_size->width;
  float vertical_resolution = bounds_height / tile_size->height;

  float* x, *y, *v;
  
  for (int i = 0; i < dataset_size; i++) {
    transformed_dataset[i * VPP] = (int)((dataset[i * VPP] - bounds->min_x) / horizontal_resolution);
    transformed_dataset[i * VPP + 1] = (int)((bounds->max_y - dataset[i * VPP + 1]) / vertical_resolution);
    transformed_dataset[i * VPP + 2] = (int)dataset[i * VPP + 2];
  }
}

};  // namespace acid_maps

