#ifndef LIB_SOURCE_SIMPLIFY_RANDOM_SIMPLIFIER_H_
#define LIB_SOURCE_SIMPLIFY_RANDOM_SIMPLIFIER_H_
/**
 * @file random_simplifier.h
 * @brief Random simplifier implementation
 *
 * Generates a uniformly distributed random dataset
 *
 * @date 2011-02-15
 * @authors Fabio R. Panettieri
 */

#include "./simplifier.h"

namespace acid_maps {

/**
 * @brief 
 */
class RandomSimplifier : public Simplifier {
  /**
   * @brief 
   */
  void simplify(Point* dataset, int dataset_size, Point* simplified_dataset, int& simplify_size);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_SIMPLIFY_RANDOM_SIMPLIFIER_H_

