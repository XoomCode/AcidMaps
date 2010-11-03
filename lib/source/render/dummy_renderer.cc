/**
 * @file dummy_renderer.cc
 * @brief Dummy renderer implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "../core/configuration.h"
#include "./dummy_renderer.h"

namespace acid_maps {

void DummyRenderer::render(Configuration* configuration) {
  int output_buffer_size = configuration->width * configuration->height * configuration->color_depth;
  
  for (int i = 0; i < output_buffer_size; i++) {
    configuration->output_buffer[i] = 0;
  }
}

};  // namespace acid_maps

