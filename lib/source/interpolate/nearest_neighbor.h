#ifndef LIB_SOURCE_INTERPOLATE_NEAREST_NEIGHBOR_H_
#define LIB_SOURCE_INTERPOLATE_NEAREST_NEIGHBOR_H_
/**
 * @file nearest_neighbor.h
 * @brief Nearest neighbor interpolation definition
 *
 * @date 2010-11-09
 * @authors Fabio R. Panettieri
 */

#include "./interpolation.h"

namespace acid_maps {

/**
 * @todo brief
 */
class NearestNeighbor : public Interpolation {
  /**
   * @todo brief
   * @param interpolation_parameter int Represents the of points to consider in a KNN
   */
  void interpolate(Size* tile_size, Pixel* dataset, int dataset_size, 
    int interpolation_parameter, float interpolated_bitmap[]);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_INTERPOLATE_NEAREST_NEIGHBOR_H_

