/**
 * @file gradient_renderer.cc
 *
 * @date 2011-03-03
 * @authors Carlos J. Farina
 */

#include "../constants/constants.h"
#include "../core/configuration.h"
#include "../core/size.h"
#include "./gradient_renderer.h"
#include <cstring>

namespace acid_maps {

/**
 * @todo Marching squares
 */ 
void GradientRenderer::render(float interpolated_bitmap[], Size* tile_size, float intervals[],
  int intervals_size, unsigned char intervals_colors[], unsigned char* output_buffer) {
  int bitmap_size = tile_size->width * tile_size->height;
	
	// TODO: 255 => constants
	float* gradient = new float[255];
	unsigned char* gradient_colors = new unsigned char[255];

	// TODO: Interpolate the intervals array and generate a larger one


  int interval_index;
  for (unsigned int i = 0; i < bitmap_size; i++) {
	  // TODO: 255 => constants
    interval_index = this->interval(interpolated_bitmap[i], gradient, 255);
    std::memcpy(output_buffer + i * RGBA, gradient_colors + interval_index * RGBA, sizeof(unsigned char) * RGBA);
  }
  
  delete[] gradient;
  delete[] gradient_colors;
}

int GradientRenderer::interval(float value, float intervals[], int intervals_size) {
  int first = 0;
  int last = intervals_size - 1;
  int mid = 0;
  
  float x = intervals[0];
  
  if (value < intervals[first]) {
    return first;
  } else if (value >= intervals[last]) {
    return last;
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

