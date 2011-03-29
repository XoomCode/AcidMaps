#ifndef LIB_SOURCE_SIMPLIFY_EXTREMES_SIMPLIFIER_H_
#define LIB_SOURCE_SIMPLIFY_EXTREMES_SIMPLIFIER_H_
/**
 * @file extremes_simplifier.h
 * @brief Extremes simplifier implementation
 *
 * Find the maximum and minimum values
 *
 * @date 2011-01-27
 * @authors Fabio R. Panettieri
 */

#include "./simplifier.h"

namespace acid_maps {

/**
 * @brief Keeps the dataset untouched
 */
class ExtremesSimplifier : public Simplifier {
  /**
   * @brief Returns a set with global extremes
   */
  void simplify(Point* dataset, int dataset_size, Point* simplified_dataset, int& simplify_size);
  
private:
  /**
   * @brief Returns if the index already exists in that array
   */
  bool in(int index, int* array, int array_size);

};

};  // namespace acid_maps

#endif  // LIB_SOURCE_SIMPLIFY_EXTREMES_SIMPLIFIER_H_

