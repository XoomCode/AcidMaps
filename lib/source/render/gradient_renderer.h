#ifndef LIB_SOURCE_RENDER_GRADIENT_RENDERER_H_
#define LIB_SOURCE_RENDER_GRADIENT_RENDERER_H_
/**
 * @file gradient_renderer.h
 * @brief Gradient renderer definition
 *
 * @date 2011-03-03
 * @authors Fabio R. Panettieri
 */

#include "./renderer.h"

namespace acid_maps {

/**
 * @brief Smooth color rendering
 */
class GradientRenderer : public Renderer {
  void render(float interpolated_bitmap[], Size* tile_size, float intervals[],
  int intervals_size, unsigned char intervals_colors[], unsigned char* output_buffer);
  
  int interval(float value, float intervals[], int intervals_size);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_RENDER_GRADIENT_RENDERER_H_
