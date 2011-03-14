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
#include "./dense_renderer.h"
#include "./sparse_renderer.h"
#include "./gradient_renderer.h"

namespace acid_maps {

Renderer* RendererFactory::get(int type) {
  switch (type) {
	  case DENSE:
      return new DenseRenderer();
    
    case SPARSE:
      return new SparseRenderer();
      
    case GRADIENT:
      return new GradientRenderer();
  }
}

};  // namespace acid_maps

