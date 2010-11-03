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
#include "./dummy_simplifier.h"

namespace acid_maps {

Simplifier* SimplifierFactory::get(int method) {
  switch (method) {
    case DUMMY:
      return new DummySimplifier();
  }
}

};  // namespace acid_maps

