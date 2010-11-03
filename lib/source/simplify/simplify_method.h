/**
 * @file simplify_method.h
 * 
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#ifndef LIB_SOURCE_SIMPLIFY_SIMPLIFY_METHOD_H_
#define LIB_SOURCE_SIMPLIFY_SIMPLIFY_METHOD_H_

namespace acid_maps {

/**
 * @brief List of available simplification methods
 */
enum SimplifyMethod {
  DEFAULT = 0,         /// No simplification
  GRID = 1,            /// Uniform distributed grid
  SAMPLING = 2,        /// Random samples
  EXTREME_VALUES = 3   /// Highest and lowest values
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_SIMPLIFY_SIMPLIFY_METHOD_H_

