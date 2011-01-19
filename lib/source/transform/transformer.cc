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

#include <cstdio>

namespace acid_maps {

/**
 * @ todo Store pixel positions in int*
 */
void Transformer::transform(Bounds* bounds, Size* tile_size, Point dataset[],
  int dataset_size, Pixel transformed_dataset[]) {

  printf("# Transformer\n\n");
  printf("# Bounds\n");
  printf("min_x: %.2f\n", bounds->min_x);
  printf("min_y: %.2f\n", bounds->min_y);
  printf("max_x: %.2f\n", bounds->max_x);
  printf("max_y: %.2f\n\n", bounds->max_y);

  float bounds_width = bounds->max_x - bounds->min_x;
  float bounds_height = bounds->max_y - bounds->min_y;
  
  printf("width: %f\n", bounds_width);
  printf("height: %f\n\n", bounds_height);

  float horizontal_resolution = bounds_width / tile_size->width;
  float vertical_resolution = bounds_height / tile_size->height;

  printf("# Horizontal resolution: %f \n", horizontal_resolution);
  printf("# Vertical resolution: %f \n\n", vertical_resolution);

  printf("# Transforming dataset :%f \n\n", vertical_resolution);  
  Pixel* pixel;
  Point* point;
  for (int i = 0; i < dataset_size; i++) {
    point = dataset + i;
    pixel = transformed_dataset + i;
    
    pixel->x = (point->x - bounds->min_x) / horizontal_resolution;
    pixel->y = (bounds->max_y - point->y) / vertical_resolution;
    pixel->value = point->value;
    
    printf("(%.2f, %.2f, %.2f) => (%d, %d, %.2f)\n", point->x, point->y, point->value, pixel->x, pixel->y, pixel->value);
  }
}

};  // namespace acid_maps

