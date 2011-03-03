#ifndef LIB_SOURCE_SIMPLIFY_NONE_SIMPLIFIER_H_
#define LIB_SOURCE_SIMPLIFY_NONE_SIMPLIFIER_H_
/**
 * @file none_simplifier.h
 * @brief None simplifier implementation
 *
 * Returns the complete dataset
 *
 * @date 2011-03-03
 * @authors Fabio R. Panettieri
 */

#include "./simplifier.h"

namespace acid_maps {

/**
 * @brief Returns the complete dataset
 */
class NoneSimplifier : public Simplifier {
  void simplify(Point* dataset, int dataset_size, Point* simplified_dataset, int& simplify_size);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_SIMPLIFY_NONE_SIMPLIFIER_H_

