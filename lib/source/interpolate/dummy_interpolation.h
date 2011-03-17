#ifndef LIB_SOURCE_INTERPOLATE_DUMMY_INTERPOLATION_H_
#define LIB_SOURCE_INTERPOLATE_DUMMY_INTERPOLATION_H_
/**
 * @file dummy_interpolation.h
 * @brief Dummy simplifier implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "./interpolation.h"

namespace acid_maps {

/**
 * @brief Does nothing
 */
class DummyInterpolation : public Interpolation {
  /**
   * @brief It allocates an empty bitmap
   */
  void interpolate(Size* tile_size, Pixel* dataset, int dataset_size, 
    int radius, float interpolated_bitmap[]);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_INTERPOLATE_DUMMY_INTERPOLATION_H_

