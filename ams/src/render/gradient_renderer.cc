/**
 * @file gradient_renderer.cc
 *
 * @date 2011-03-03
 * @authors Carlos J. Farina
 *          Fabio R. Panettieri
 */

#include "./gradient_renderer.h"

#include <cstring>
#include <cmath>

#include "../constants/constants.h"
#include "../core/color.h"
#include "../core/configuration.h"
#include "../core/size.h"


namespace acid_maps {

/**
 * @todo Marching squares
 */ 
void GradientRenderer::render(float interpolated_bitmap[], Size* tile_size, float intervals[],
  int intervals_size, Color* intervals_colors, unsigned char* output_buffer) {
  
  // Size of the bitmap being interpolated
  int bitmap_size = tile_size->width * tile_size->height;

  // In order to generate smooth interpolations, a larger interpolated interval set is generated
  float* gradient = new float[GRADIENT_INTERVAL_SIZE];

  // Interpolated colors
  Color* gradient_colors = new Color[GRADIENT_INTERVAL_SIZE];

  // Color used to interpolate the smooth intervals
  Color* start_color, *end_color;
  Color* interpolated_color = new Color();

  // Number of colors in the current range
  unsigned int color_steps;

  // Gradient offset acummulator. Used to store the offset between multiple interpolations
  unsigned int offset = 0;

  // Helper variables used to generate interpolated intervals
  float interval_step, interpolated_interval;

  // Helper variables used to split ranges proportionally
  float global_range = intervals[intervals_size - 1] - intervals[0];
  float local_range;

  for (unsigned int i = 0; i < (intervals_size - 1); i++) {
    local_range = intervals[i + 1] - intervals[i];
    color_steps = (unsigned int)std::abs(GRADIENT_INTERVAL_SIZE * (local_range / global_range));
    interval_step = (intervals[i + 1] - intervals[i]) / color_steps;

    start_color = intervals_colors + i;
    end_color = intervals_colors + i + 1;

    float coefficient = 0;
    for (int k = 0; k < color_steps; k++) {
      coefficient = k / color_steps;
      interpolated_interval = intervals[i] + interval_step * k;
      std::memcpy(gradient + offset + k, &interpolated_interval, sizeof(interpolated_interval));

      interpolated_color->r = (unsigned char)(end_color->r * coefficient + start_color->r * (1 - coefficient));
      interpolated_color->g = (unsigned char)(end_color->g * coefficient + start_color->g * (1 - coefficient));
      interpolated_color->b = (unsigned char)(end_color->b * coefficient + start_color->b * (1 - coefficient));
      interpolated_color->a = (unsigned char)(end_color->a * coefficient + start_color->a * (1 - coefficient));

      std::memcpy(gradient_colors + offset + k, interpolated_color, sizeof(Color));
    }
    offset += color_steps;
  }

  std::memcpy(gradient + GRADIENT_INTERVAL_SIZE - 1, intervals + intervals_size - 1, sizeof(intervals));
  std::memcpy(gradient_colors + GRADIENT_INTERVAL_SIZE - 1, intervals_colors + intervals_size - 1, sizeof(intervals_colors));

  int interval_index;
  for (unsigned int i = 0; i < bitmap_size; i++) {
    interval_index = this->interval(interpolated_bitmap[i], gradient, GRADIENT_INTERVAL_SIZE);
    std::memcpy(output_buffer + i * RGBA, gradient_colors + interval_index, sizeof(Color));
  }

  delete interpolated_color;
  delete[] gradient;
  delete[] gradient_colors;
}

int GradientRenderer::interval(float value, float intervals[], int intervals_size) {
  int first = 0;
  int last = intervals_size - 1;
  int mid = 0;

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

  // HACK: changed -1 to avoid segmentation faults.
  // This error should be made explicit
  return 0;
}


};  // namespace acid_maps

