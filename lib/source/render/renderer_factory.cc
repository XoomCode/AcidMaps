/**
 * @file renderer_factory.cc
 * @brief Renderer factory implementation
 *
 * @date 2010-11-08
 * @authors Fabio R. Panettieri
 */
#include "./renderer.h"
#include "./renderer_factory.h"
#include "./renderer_type.h"
#include "./sparse_renderer.h"

namespace acid_maps {

Renderer* RendererFactory::get(int type) {
  switch (type) {
    case SPARSE:
      return new SparseRenderer();
  }
}

};  // namespace acid_maps

