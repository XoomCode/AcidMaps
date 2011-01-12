/**
 * @file copy_simplifier.cc
 * @brief Copy simplifier implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "./copy_simplifier.h"
#include <cstring>

namespace acid_maps {

void CopySimplifier::simplify(float dataset[], int dataset_size, int simplify_size, float simplified_dataset[]) {
  int size = simplify_size <= dataset_size ? simplify_size : dataset_size;
  std::memcpy((float*)simplified_dataset, (float*)dataset, sizeof(float) * size * VPP);
}

};  // namespace acid_maps

