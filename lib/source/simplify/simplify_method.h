#ifndef LIB_SOURCE_SIMPLIFY_SIMPLIFY_METHOD_H_
#define LIB_SOURCE_SIMPLIFY_SIMPLIFY_METHOD_H_
/**
 * @file simplify_method.h
 * 
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

namespace acid_maps {

/**
 * @brief List of available simplification methods
 */
enum SimplifyMethod {
  COPY = 0,             /// Copy the first values
  GRID = 1,             /// Uniform distributed grid
  RANDOM = 2,           /// Random samples
  EXTREMES = 3          /// Highest and lowest values
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_SIMPLIFY_SIMPLIFY_METHOD_H_

