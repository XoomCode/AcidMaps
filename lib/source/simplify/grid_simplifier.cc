/**
 * @file grid_simplifier.cc
 * @brief Grid simplifier implementation
 *
 * @date 2011-01-12
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "./grid_simplifier.h"

namespace acid_maps {

void GridSimplifier::simplify(float dataset[], int dataset_size, int simplify_size, float simplified_dataset[]) {
  int size = simplify_size <= dataset_size ? simplify_size : dataset_size;
}

};  // namespace acid_maps

