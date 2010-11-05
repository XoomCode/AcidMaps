/**
 * @file dummy_simplifier.cc
 * @brief Dummy simplifier implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "./dummy_simplifier.h"

namespace acid_maps {

void DummySimplifier::simplify(float* dataset, int dataset_size, int simplify_size, float* simplified_dataset) {
  int size = simplify_size <= dataset_size ? simplify_size : dataset_size;
  for (int i = 0; i < size; i++) {
    simplified_dataset[i * VPP] = dataset[i * VPP];
    simplified_dataset[i * VPP + 1] = dataset[i * VPP + 1];
    simplified_dataset[i * VPP + 2] = dataset[i * VPP + 2];
  }
}

};  // namespace acid_maps

