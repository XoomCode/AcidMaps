#ifndef LIB_SOURCE_SIMPLIFY_COPY_SIMPLIFIER_H_
#define LIB_SOURCE_SIMPLIFY_COPY_SIMPLIFIER_H_
/**
 * @file copy_simplifier.h
 * @brief Copy simplifier implementation
 *
 * Keeps the dataset untouched
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "./simplifier.h"

namespace acid_maps {

/**
 * @brief Keeps the dataset untouched
 */
class CopySimplifier : public Simplifier {
  /**
   * @brief It does nothing with the dataset
   */
  void simplify(Point* dataset, int dataset_size, Point* simplified_dataset, int& simplify_size);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_SIMPLIFY_COPY_SIMPLIFIER_H_

