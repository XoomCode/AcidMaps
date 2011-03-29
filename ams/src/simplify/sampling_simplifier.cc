/**
 * @file sampling_simplifier.cc
 * @brief Sampling simplifier implementation
 *
 * @date 2011-02-15
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/point.h"
#include "./sampling_simplifier.h"
#include <cstring>
#include <cstdlib>

namespace acid_maps {

void SamplingSimplifier::simplify(Point* dataset, int dataset_size, Point* simplified_dataset, int& simplify_size) {
  if (dataset_size < simplify_size) simplify_size = dataset_size;
  if (simplify_size == 0) return;
  
  int step = dataset_size / simplify_size;
  for(int i = 0; i < simplify_size; i++){
    std::memcpy(simplified_dataset + i, dataset + i * step, sizeof(Point));
  }
}

};  // namespace acid_maps

