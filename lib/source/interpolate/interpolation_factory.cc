/**
 * @file interpolation_factory.cc
 * @brief Interpolation factory implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */
#include "./interpolation.h"
#include "./interpolation_factory.h"
#include "./interpolation_strategy.h"
#include "./dummy_interpolation.h"

namespace acid_maps {

Interpolation* InterpolationFactory::get(int strategy) {
  switch (strategy) {
    case DUMMY:
      return new DummyInterpolation();
  }
}

};  // namespace acid_maps

