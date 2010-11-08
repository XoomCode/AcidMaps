#ifndef LIB_SOURCE_CONFIGURATION_H_
#define LIB_SOURCE_CONFIGURATION_H_
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

#include "./bounds.h"
#include "./size.h"

namespace acid_maps {

/**
 * @brief 
 * 
 * @todo Brief and description
 */
struct Configuration {
  /// Set of valued points, stored 3 floats per point. X, Y, Value
  float dataset[];

  /// Number of points in the dataset
  /// @note Each point is composed of 3 floats, X, Y, Value
  int dataset_size;
  
  /// Desired simplify method
  int simplify_method;

  /// Size of the simplified sample
  int simplify_size;
  
  /// Requested tile bounds
  Bounds* bounds;
  
  /// Strategy used to interpolate missing values
  int interpolation_strategy;
  
  /// Strategy used to interpolate missing values
  int interpolation_parameter;
  
  /// Output image size
  Size* tile_size;
  
  /// Intervals array
  int intervals[];
  
  /// Intervals array
  unsigned char interval_colors[];
  
  /// Size of the itervals array
  int intervals_size;
  
  /// Determines how intervals are going to be accessed in the rendering step
  int intervals_type;
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_CONFIGURATION_H_

