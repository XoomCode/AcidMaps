#ifndef LIB_SOURCE_INTERPOLATE_DUMMY_INTERPOLATION_H_
#define LIB_SOURCE_INTERPOLATE_DUMMY_INTERPOLATION_H_
/**
 * @file dummy_interpolation.h
 * @brief Dummy simplifier implementation
 *
 * Keeps the dataset untouched
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
  void interpolate(Configuration* configuration);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_INTERPOLATE_DUMMY_INTERPOLATION_H_

