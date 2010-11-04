/**
 * @file configuration.cc
 * @brief Configuration implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "./configuration.h"

#define NULL 0

namespace acid_maps {

Configuration::Configuration() {
  dataset = NULL;
  dataset_size = 0;
  simplify_method = 0;
  simplify_size = 0;
  bounds = NULL;
  width = 0;
  height = 0;
  color_depth = 0;
  interpolated_bitmap = NULL;
}

Configuration::~Configuration() {
  // if (interpolated_bitmap) delete [] interpolated_bitmap;
  // if (bounds) delete bounds;
  // if (dataset) delete [] dataset;
}

};  // namespace acid_maps

