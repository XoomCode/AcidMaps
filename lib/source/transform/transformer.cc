/**
 * @file transformer.cc
 * @brief Transformer implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "../core/configuration.h"
#include "./transformer.h"

namespace acid_maps {

void Transformer::transform(Configuration* configuration) {

  float bounds_width = configuration->bounds->right - configuration->bounds->left;
  float bounds_height = configuration->bounds->top - configuration->bounds->bottom;
  
  float horizontal_resolution = bounds_width / configuration->width;
  float vertical_resolution = bounds_height / configuration->height;
  
  for (int i = 0; i < configuration->dataset_size; i++) {
    
  }
  
}

};  // namespace acid_maps

