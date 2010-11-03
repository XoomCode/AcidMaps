/**
 * @file configuration.h
 * @brief 
 * 
 * @date 2010-11-02
 * @authors Fabio R. Panettieri
 * 
 * @todo Brief and description
 * 
 */

#ifndef LIB_SOURCE_CONFIGURATION_H_
#define LIB_SOURCE_CONFIGURATION_H_

namespace acid_maps {

/**
 * @brief 
 * 
 * @todo Brief and description
 */
struct Configuration {
  /// Output image width
  int width;

  /// Output image height
  int height;

  /// Bits per pixel. Allowed values are 24(RGB) or 32(RGBA)
  int color_depth;

  /// Desired simplify method
  int simplify_method;

  /// Size of the simplified sample
  int simplify_size;

  /// Set of valued points, stored 3 floats per point. X, Y, Value
  float* dataset;

  /// Number of points in the dataset
  /// @note Each point is composed of 3 floars, X, Y, Value
  int dataset_size;
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_CONFIGURATION_H_

