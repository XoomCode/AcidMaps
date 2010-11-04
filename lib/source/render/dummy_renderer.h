#ifndef LIB_SOURCE_RENDER_DUMMY_RENDERER_H_
#define LIB_SOURCE_RENDER_DUMMY_RENDERER_H_
/**
 * @file dummy_renderer.h
 * @brief Dummy renderer implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "./renderer.h"

namespace acid_maps {

/**
 * @brief Renders nothing
 */
class DummyRenderer : public Renderer {
  /**
   * @brief It fills the output_buffer with 0
   */
  void render(Configuration* configuration);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_RENDER_DUMMY_RENDERER_H_

