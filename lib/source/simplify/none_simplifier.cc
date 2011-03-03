/**
 * @file none_simplifier.cc
 * @brief None simplifier implementation
 *
 * @date 2011-03-03
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/point.h"
#include "./none_simplifier.h"
#include <cstring>

namespace acid_maps {

void NoneSimplifier::simplify(Point* dataset, int dataset_size, Point* simplified_dataset, int& simplify_size) {
  delete[] simplified_dataset;
	simplify_size = dataset_size;
  simplified_dataset = new Point[dataset_size];
  std::memcpy(simplified_dataset, dataset, sizeof(Point) * dataset_size);
}

};  // namespace acid_maps

