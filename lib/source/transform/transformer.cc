/**
 * @file transformer.cc
 * @brief Transformer implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "../core/bounds.h"
#include "../core/configuration.h"
#include "./transformer.h"

namespace acid_maps {

/**
 * @ todo Store pixel positions in int*
 */
void Transformer::transform(Configuration* configuration) {
  Bounds* bounds = configuration->bounds;
  float bounds_width = bounds->max_x - bounds->min_x;
  float bounds_height = bounds->max_y - bounds->min_y;

  float horizontal_resolution = bounds_width / configuration->width;
  float vertical_resolution = bounds_height / configuration->height;

  /**
   * Each point is a set of 3 floats
   * We iterate throught the dataset with a step of 3
   */
  float* x, *y, *v;
  int step = 3;
  for (int i = 0; i < configuration->dataset_size; i++) {
    x = configuration->dataset + i * step;
    y = configuration->dataset + i * step + 1;
    v = configuration->dataset + i * step + 2;
    
    *x = (*x - bounds->min_x) / horizontal_resolution;
    *y = (bounds->max_y - *y) / vertical_resolution;
  }
}

};  // namespace acid_maps

