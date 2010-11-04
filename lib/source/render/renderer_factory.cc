/**
 * @file renderer_factory.cc
 * @brief Renderer factory implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */
#include "./renderer.h"
#include "./renderer_factory.h"
#include "./color_depth.h"
#include "./dummy_renderer.h"

namespace acid_maps {

Renderer* RendererFactory::get(int color_depth) {
  return new DummyRenderer();
}

};  // namespace acid_maps

