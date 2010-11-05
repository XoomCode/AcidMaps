/**
 * @file dummy_renderer.cc
 * @brief Dummy renderer implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "../core/configuration.h"
#include "./renderer.h"

#define RGBA 4

namespace acid_maps {

void Renderer::render(Configuration* configuration, unsigned char* output_buffer) {
  int output_buffer_size = configuration->width * configuration->height * RGBA;
  
  for (int i = 0; i < output_buffer_size; i++) {
    output_buffer[i] = 0;
  }
}

};  // namespace acid_maps

