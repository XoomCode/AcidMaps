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

void Transformer::transform(Configuration* configuration) {
  Bounds* bounds = configuration->bounds;
  float bounds_width = bounds->right - bounds->left;
  float bounds_height = bounds->top - bounds->bottom;

  float horizontal_resolution = bounds_width / configuration->width;
  float vertical_resolution = bounds_height / configuration->height;

  /**
   * Each point is a set of 3 floats
   * We iterate throught the dataset with a step of 3
   */
  int step = 3;
  for (int i = 0; i < configuration->dataset_size; i += step) {
    configuration->dataset[i] = (configuration->dataset[i] - bounds->left) * horizontal_resolution;
    configuration->dataset[i+1] = -1 * (configuration->dataset[i+1] - bounds->top) * vertical_resolution;
  }
}

};  // namespace acid_maps

