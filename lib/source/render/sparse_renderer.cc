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
      interval_index = this->find_interval(interpolated_bitmap[pixel], intervals, intervals_size);
      std::memcpy((unsigned char*)output_buffer[pixel * RGBA], (unsigned char*)intervals_colors[interval_index], sizeof(unsigned char) * RGBA);
    }
  }
}

int SparseRenderer::find_interval(int value, int intervals[], int intervals_size) {
  int low = 0;
  int high = intervals_size - 1;
  int mid;
  while (low <= high) {
    mid = (low + high) / 2;
    if (value > intervals[mid]) {
      low = mid + 1;
    } else if (value < intervals[mid]) {
      high = mid - 1;
    } else {
      break;
    }
  }
  return mid;
}

};  // namespace acid_maps

