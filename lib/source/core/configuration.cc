/**
 * @file configuration.cc
 * @brief Configuration implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "./configuration.h"

namespace acid_maps {

Configuration::Configuration() {
  dataset = 0;
  dataset_size = 0;
  simplify_method = 0;
  simplify_size = 0;
  tile_bounds = new Bounds();
  map_bounds = new Bounds();
  width = 0;
  height = 0;
  color_depth = 0;
}

Configuration::~Configuration() {
  delete map_bounds;
  delete tile_bounds;
  delete [] dataset;
}

};  // namespace acid_maps

