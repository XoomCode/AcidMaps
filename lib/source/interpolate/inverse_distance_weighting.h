#ifndef LIB_SOURCE_INTERPOLATE_IDW_H_
#define LIB_SOURCE_INTERPOLATE_IDW_H_
/**
 * @file inverse_distance_weighting.h
 * @brief Inverse Distance Weighted Interpolation
 *
 * @date 2011-01-05
 * @authors Fabio R. Panettieri
 */

#include "./interpolation.h"

namespace acid_maps {

/**
 * @todo brief and description
 */
class InverseDistanceWeighting : public Interpolation {
  /**
   * @todo brief and description
   */
  void interpolate(Size* tile_size, int dataset[], int dataset_size, 
    int interpolation_parameter, int interpolated_bitmap[]);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_INTERPOLATE_LINEAR_INTERPOLATION_H_

