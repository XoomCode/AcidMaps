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
#include "./nearest_neighbor.h"
#include "./linear_interpolation.h"
#include "./inverse_distance_weighting.h"

namespace acid_maps {

Interpolation* InterpolationFactory::get(int strategy) {
  switch (strategy) {
    case NEAREST_NEIGHBOR:
      return new NearestNeighbor();
    
    case LINEAR:
      return new LinearInterpolation();
    
    case INVERSE_DISTANCE_WEIGHTING:
      return new InverseDistanceWeighting();
      
    default:
      return new DummyInterpolation();
  }
}

};  // namespace acid_maps

