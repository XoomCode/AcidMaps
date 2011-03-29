#ifndef LIB_SOURCE_SIMPLIFY_GRID_SIMPLIFIER_H_
#define LIB_SOURCE_SIMPLIFY_GRID_SIMPLIFIER_H_
/**
 * @file grid_simplifier.h
 * @brief Grid simplifier implementation
 *
 * A double pass simplification
 * The first step it iterates through the complete dataset 
 * calculating the bounding box and generates a grid
 *
 * The second step iterates through the dataset acummulating its
 * value in the grid
 *
 * The third step we calculate the average
 *
 * @date 2011-01-12
 * @authors Fabio R. Panettieri
 */

#include "./simplifier.h"

namespace acid_maps {

/**
 * @brief Keeps the dataset untouched
 */
class GridSimplifier : public Simplifier {
  /**
   * @brief It does nothing with the dataset
   */
  void simplify(Point* dataset, int dataset_size, Point* simplified_dataset, int& simplify_size);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_SIMPLIFY_GRID_SIMPLIFIER_H_

