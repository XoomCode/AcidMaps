/**
 * @file dummy_renderer.cc
 * @brief Dummy renderer implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/configuration.h"
#include "./renderer.h"

namespace acid_maps {

void Renderer::render(Size* tile_size, int* bitmap, unsigned char* output_buffer) {
  int output_buffer_size = tile_size->width * tile_size->height * RGBA;
  
  for (int i = 0; i < output_buffer_size; i++) {
    output_buffer[i] = 0;
  }
}

};  // namespace acid_maps

