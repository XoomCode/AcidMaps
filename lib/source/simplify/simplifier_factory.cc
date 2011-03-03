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
#include "./none_simplifier.h"
#include "./copy_simplifier.h"
#include "./grid_simplifier.h"
#include "./sampling_simplifier.h"
#include "./extremes_simplifier.h"

namespace acid_maps {

Simplifier* SimplifierFactory::get(int method) {
  switch (method) {
  	case NONE:
      return new NoneSimplifier();
      
    case COPY:
      return new CopySimplifier();
    
    case GRID:
      return new GridSimplifier();
    
    case SAMPLING:
      return new SamplingSimplifier();
      
    case EXTREMES:
      return new ExtremesSimplifier();
  }
}

};  // namespace acid_maps

