/**
 * @file dense_renderer.cc
 *
 * @date 2011-03-14
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/color.h"
#include "../core/configuration.h"
#include "../core/size.h"
#include "./dense_renderer.h"
#include <cstring>

namespace acid_maps {

/**
 * @todo Marching squares
 */ 
void DenseRenderer::render(float interpolated_bitmap[], Size* tile_size, float intervals[],
  int intervals_size, Color* intervals_colors, unsigned char* output_buffer) {
  int interval_index;
  int bitmap_size = tile_size->width * tile_size->height;

  for (unsigned int i = 0; i < bitmap_size; i++) {
  	interval_index = this->interval(interpolated_bitmap[i], intervals, intervals_size);
    std::memcpy(output_buffer + i * RGBA, intervals_colors + interval_index, sizeof(Color));
  }
}

int DenseRenderer::interval(float value, float intervals[], int intervals_size) {
  if(value < 0) return 0;
  if(value >= intervals_size) return intervals_size - 1;
  return value;
}


};  // namespace acid_maps

