/**
 * @file grid_simplifier.cc
 * @brief Grid simplifier implementation
 *
 * @date 2011-01-12
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/point.h"
#include "./grid_simplifier.h"
#include <climits>
#include <cmath>

namespace acid_maps {

void GridSimplifier::simplify(Point* dataset, int dataset_size, int simplify_size, Point* simplified_dataset) {
  int size = simplify_size <= dataset_size ? simplify_size : dataset_size;
  
  // Step 1: Get the bounding box
  float min_x = INT_MAX;
  float min_y = INT_MAX;
  float max_x = INT_MIN;
  float max_y = INT_MIN;
  
  for (int i = 0; i < size; i++){
  
  }
  
  // Step 2: Create the NxN simplified grid
  // In order to create a NxN proportional grid that will allow us to simplify the dataset
  // we need to calculate the closest perfect square number to get N
  int side = std::floor(std::sqrt(size));
  
}

};  // namespace acid_maps

