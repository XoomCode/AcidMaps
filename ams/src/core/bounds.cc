/**
 * @file bounds.cc
 * @brief Bounds implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "./bounds.h"

namespace acid_maps {

Bounds::Bounds() {
  min_x = 0.0;
  min_y = 0.0;
  max_x = 0.0;
  max_y = 0.0;
}

Bounds::Bounds(float min_x, float min_y, float max_x, float max_y) {
  this->min_x = min_x;
  this->min_y = min_y;
  this->max_x = max_x;
  this->max_y = max_y;
}

};  // namespace acid_maps

