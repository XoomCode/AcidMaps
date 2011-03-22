#ifndef LIB_SOURCE_INTERPOLATE_INTERPOLATION_STRATEGY_H_
#define LIB_SOURCE_INTERPOLATE_INTERPOLATION_STRATEGY_H_
/**
 * @file interpolation_strategy.h
 * 
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

namespace acid_maps {

/**
 * @brief List of available simplification methods
 */
enum InterpolationStrategy {
  DUMMY = 0,                       /// No interpolation uses the assigned value
  NEAREST_NEIGHBOR = 1,            /// N Neighbors found
  LINEAR = 2,                      /// Value decays with distance
  INVERSE_DISTANCE_WEIGHTING = 3   /// Simple implementation of IDW
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_INTERPOLATE_INTERPOLATION_STRATEGY_H_

