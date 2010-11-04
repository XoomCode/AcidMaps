/**
 * @file dummy_interpolation.cc
 * @brief Dummy interpolation implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "../core/configuration.h"
#include "./dummy_interpolation.h"

namespace acid_maps {

void DummyInterpolation::interpolate(Configuration* configuration) {
  int bitmap_size = configuration->width * configuration->height;
  configuration->interpolated_bitmap = new unsigned int[bitmap_size];
  
  for (int i = 0; i < bitmap_size; i++) {
    configuration->interpolated_bitmap[i] = 0;
  }
}

};  // namespace acid_maps

