/**
 * @file sparse_renderer.cc
 *
 * @date 2010-11-08
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/configuration.h"
#include "../core/size.h"
#include "./sparse_renderer.h"
#include <cstring>

namespace acid_maps {

/**
 * @todo Marching squares
 */ 
void SparseRenderer::render(Size* tile_size, int interpolated_bitmap[], int intervals[],
    int intervals_size, unsigned char intervals_colors[], unsigned char output_buffer[]) {
  int pixel, interval_index;
  for (int x = 0; x < tile_size->width; x++) {
    for (int y = 0; y < tile_size->height; y++) {
      pixel = y * tile_size->width + x;
      interval_index = this->interval(interpolated_bitmap[pixel], intervals, intervals_size);
      std::memcpy((unsigned char*)output_buffer[pixel * RGBA], (unsigned char*)intervals_colors[interval_index], sizeof(unsigned char) * RGBA);
    }
  }
}

int SparseRenderer::interval(int value, int intervals[], int intervals_size) {
  int index;
  for (index = 0; index < intervals_size - 1; index++) {
    if (value <= intervals[index] ) {
      break;
    }
  }
  return index;
}

};  // namespace acid_maps

