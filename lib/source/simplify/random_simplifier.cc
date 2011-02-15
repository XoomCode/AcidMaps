/**
 * @file random_simplifier.cc
 * @brief Random simplifier implementation
 *
 * @date 2011-02-15
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/point.h"
#include "./random_simplifier.h"
#include <cstring>
#include <cstdlib>
#include <ctime>

namespace acid_maps {

void RandomSimplifier::simplify(Point* dataset, int dataset_size, Point* simplified_dataset, int& simplify_size) {
  if (dataset_size < simplify_size) simplify_size = dataset_size;
  if (simplify_size == 0) return;
  
  std::srand ( std::time(NULL) );
   
  int step = dataset_size / simplify_size;
  int offset;
  for(int i = 0; i < simplify_size; i++){
    offset = std::rand() % step;
    std::memcpy(simplified_dataset + i, dataset + i * step + offset, sizeof(Point));
  }
}

};  // namespace acid_maps

