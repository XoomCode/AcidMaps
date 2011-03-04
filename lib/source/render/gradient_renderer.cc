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
#include <cmath>



#include <stdio.h>



namespace acid_maps {

/**
 * @todo Marching squares
 */ 
void GradientRenderer::render(float interpolated_bitmap[], Size* tile_size, float intervals[],
  int intervals_size, unsigned char intervals_colors[], unsigned char* output_buffer) {
  int bitmap_size = tile_size->width * tile_size->height;
	
  float* gradient = new float[GRADIENT_INTERVAL_SIZE];
  unsigned char* gradient_colors = new unsigned char[GRADIENT_INTERVAL_SIZE * RGBA];

  float total_range = intervals[intervals_size - 1] - intervals[0];

  float num_step;
  int start_alpha, start_red, start_green, start_blue;
  int end_alpha, end_red, end_green, end_blue;
  unsigned char interpolated_value;
  unsigned int gradient_index = 0;

  float start_interval, step_interval, current_interval;
  float parcial_range;
  for(unsigned int i = 0; i < (intervals_size - 1); i++){
    parcial_range = intervals[i + 1] - intervals[i];
	num_step = std::abs(GRADIENT_INTERVAL_SIZE * (parcial_range/total_range));

	start_red = intervals_colors[i * RGBA + 0];
	start_green = intervals_colors[i * RGBA + 1];
	start_blue = intervals_colors[i * RGBA + 2];
	start_alpha = intervals_colors[i * RGBA + 3];

	end_red = intervals_colors[i * RGBA + 4];
	end_green = intervals_colors[i * RGBA + 5];
	end_blue = intervals_colors[i * RGBA + 6];
	end_alpha = intervals_colors[i * RGBA + 7];

	step_interval = (intervals[i+1] - intervals[i])/num_step;

	float coefficient = 0;
    for(int k = 0; k < num_step; k++) {
		coefficient = k / num_step;
    	current_interval = intervals[i] + step_interval * k;
		std::memcpy(gradient + gradient_index + k, &current_interval, sizeof(float));

    	interpolated_value = (end_red * coefficient + start_red * (1 - coefficient));
		std::memcpy(gradient_colors + (gradient_index + k )* RGBA, &interpolated_value, sizeof(unsigned char));

		interpolated_value = (end_green * coefficient + start_green * (1- coefficient));
		std::memcpy(gradient_colors + (gradient_index + k) * RGBA + 1, &interpolated_value, sizeof(unsigned char));

		interpolated_value = (end_blue * coefficient + start_blue * (1- coefficient));
		std::memcpy(gradient_colors + (gradient_index + k) * RGBA + 2, &interpolated_value, sizeof(unsigned char));

		interpolated_value = (end_alpha * coefficient + start_alpha * (1- coefficient));
		std::memcpy(gradient_colors + (gradient_index + k) * RGBA + 3, &interpolated_value, sizeof(unsigned char));

    }

	gradient_index += num_step;
  }
  std::memcpy(gradient + GRADIENT_INTERVAL_SIZE - 1, intervals + intervals_size - 1, sizeof(float));
  std::memcpy(gradient_colors + (GRADIENT_INTERVAL_SIZE - 1) * RGBA, intervals_colors + (intervals_size - 1) * RGBA, sizeof(unsigned char) * RGBA);

  int interval_index;
  for (unsigned int i = 0; i < bitmap_size; i++) {
    interval_index = this->interval(interpolated_bitmap[i], gradient, GRADIENT_INTERVAL_SIZE);
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

