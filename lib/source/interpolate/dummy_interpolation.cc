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
  configuration->interpolated_bitmap = new int[configuration->width * configuration->height];
}

};  // namespace acid_maps

