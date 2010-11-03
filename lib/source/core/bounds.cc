/**
 * @file configuration.cc
 * @brief Configuration implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "./bounds.h"

namespace acid_maps {

Bounds::Bounds() {
  left = 0;
  bottom = 0;
  right = 0;
  top = 0;
}

Bounds::Bounds(int left, int bottom, int right, int top) {
  this->left = left;
  this->bottom = bottom;
  this->right = right;
  this->top = top;      
}

};  // namespace acid_maps

