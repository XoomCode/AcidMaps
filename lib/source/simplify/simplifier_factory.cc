/**
 * @file simplifier_factory.cc
 * @brief Simplifier factory implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */
#include "./simplifier.h"
#include "./simplify_method.h"
#include "./simplifier_factory.h"
#include "./copy_simplifier.h"
#include "./grid_simplifier.h"

namespace acid_maps {

Simplifier* SimplifierFactory::get(int method) {
  switch (method) {
    case COPY:
      return new CopySimplifier();
    
    case GRID:
      return new GridSimplifier();
  }
}

};  // namespace acid_maps

