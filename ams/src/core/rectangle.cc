/**
 * @file rectangle.cc
 * @brief Rectangle implementation
 *
 * @date 2010-11-09
 * @authors Fabio R. Panettieri
 */

#include "./rectangle.h"

namespace acid_maps {

Rectangle::Rectangle() {
  min_x = 0;
  min_y = 0;
  max_x = 0;
  max_y = 0;
}

Rectangle::Rectangle(int min_x, int min_y, int max_x, int max_y) {
  this->resize(min_x, min_y, max_x, max_y);
}

void Rectangle::resize(int min_x, int min_y, int max_x, int max_y) {
  this->min_x = min_x;
  this->min_y = min_y;
  this->max_x = max_x;
  this->max_y = max_y;
}

void Rectangle::intersect(int min_x, int min_y, int max_x, int max_y) {
  this->min_x = this->min_x > min_x ? this->min_x : min_x;
  this->min_y = this->min_y > min_y ? this->min_y : min_y;
  this->max_x = this->max_x < max_x ? this->max_x : max_x;
  this->max_y = this->max_y < max_y ? this->max_y : max_y;
}

};  // namespace acid_maps

