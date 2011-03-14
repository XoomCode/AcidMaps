#ifndef LIB_SOURCE_RENDER_DENSE_RENDERER_H_
#define LIB_SOURCE_RENDER_DENSE_RENDERER_H_
/**
 * @file dense_renderer.h
 * @brief Dense renderer definition
 *
 * @date 2011-03-14
 * @authors Fabio R. Panettieri
 */

#include "./renderer.h"

namespace acid_maps {

/**
 * @brief Renderer optimized for direct access
 */
class DenseRenderer : public Renderer {
  void render(float interpolated_bitmap[], Size* tile_size, float intervals[],
  	int intervals_size, Color* intervals_colors, unsigned char* output_buffer);
  	
  int interval(float value, float intervals[], int intervals_size);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_RENDER_DENSE_RENDERER_H_
