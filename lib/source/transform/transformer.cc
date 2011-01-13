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
#include "../core/point.h"
#include "../core/pixel.h"
#include "./transformer.h"

namespace acid_maps {

/**
 * @ todo Store pixel positions in int*
 */
void Transformer::transform(Bounds* bounds, Size* tile_size, Point* dataset,
  int dataset_size, Pixel* transformed_dataset) {

  float bounds_width = bounds->max_x - bounds->min_x;
  float bounds_height = bounds->max_y - bounds->min_y;

  float horizontal_resolution = bounds_width / tile_size->width;
  float vertical_resolution = bounds_height / tile_size->height;

  Pixel* pixel;
  Point* point;
  for (int i = 0; i < dataset_size; i++) {
    pixel = transformed_dataset + i;
    point = dataset + i;
    
    pixel->x = (point->x - bounds->min_x) / horizontal_resolution;
    pixel->y = (bounds->max_y - point->y) / vertical_resolution;
    pixel->value = point->value;
  }
}

};  // namespace acid_maps

