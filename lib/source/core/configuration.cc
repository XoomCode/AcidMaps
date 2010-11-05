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
  interpolation_strategy = 0;
  interpolation_parameter = 0;
  width = 0;
  height = 0;
}

Configuration::~Configuration() {
  if (bounds) delete bounds;
  if (dataset) delete [] dataset;
}

};  // namespace acid_maps

