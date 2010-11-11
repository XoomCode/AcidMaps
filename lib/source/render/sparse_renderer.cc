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
void SparseRenderer::render(int interpolated_bitmap[], Size* tile_size, int intervals[],
    int intervals_size, unsigned char intervals_colors[], unsigned char* output_buffer) {
  int interval_index;
  int bitmap_size = tile_size->width * tile_size->height;
  
  for (unsigned int i = 0; i < bitmap_size; i++) {
    interval_index = this->interval(interpolated_bitmap[i], intervals, intervals_size);
    std::memcpy(output_buffer + i * RGBA, intervals_colors + interval_index, sizeof(unsigned char) * RGBA);
  }
}

int SparseRenderer::interval(int value, int intervals[], int intervals_size) {
  int first = 0;
  int last = intervals_size - 1;
  int mid;
  
  if (value >= intervals[last]) {
    return last;
  } else if (value < intervals[first]) {
    return first;
  }
  
  while (first <= last) {
    mid = (first + last) / 2;
    if (value > intervals[mid]) {  
      first = mid + 1;
    } else if (value < intervals[mid]) {
      if (mid >= 1 && value > intervals[mid - 1]) {
        return mid;
      } else {
        last = mid - 1;
      }
    } else {
      return mid;
    }
  }
  return -1;
}


};  // namespace acid_maps

