#ifndef LIB_SOURCE_INTERPOLATE_LINEAR_INTERPOLATION_H_
#define LIB_SOURCE_INTERPOLATE_LINEAR_INTERPOLATION_H_
/**
 * @file linear_interpolation.h
 * @brief Linear interpolation implementation
 *
 * @date 2010-11-09
 * @authors Fabio R. Panettieri
 */

#include "./interpolation.h"

namespace acid_maps {

/**
 * @todo brief and description
 */
class LinearInterpolation : public Interpolation {
  /**
   * @todo brief and description
   */
  void interpolate(Size* tile_size, Pixel* dataset, int dataset_size, 
    int interpolation_parameter, float interpolated_bitmap[]);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_INTERPOLATE_LINEAR_INTERPOLATION_H_

