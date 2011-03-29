/**
 * @file size.cc
 * @brief Size implementation
 *
 * @date 2010-11-05
 * @authors Fabio R. Panettieri
 */

#include "./size.h"

namespace acid_maps {

Size::Size() {
  width = 0;
  height = 0;
}

Size::Size(int width, int height) {
  this->width = width;
  this->height = height;
}

};  // namespace acid_maps

