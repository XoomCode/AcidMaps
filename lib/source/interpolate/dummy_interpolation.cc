/**
 * @file dummy_interpolation.cc
 * @brief Dummy interpolation implementation
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/configuration.h"
#include "./dummy_interpolation.h"
#include <cstring>

namespace acid_maps {

void DummyInterpolation::interpolate(Size* tile_size, int dataset[], int dataset_size, int interpolated_bitmap[]) {
  std::memset(interpolated_bitmap, 0, dataset_size * sizeof(interpolated_bitmap[0]));
  
  int* x, *y, *v;
  for (int i = 0; i < dataset_size; i++) {
    x = dataset + VPP * i;
    y = dataset + VPP * i + 1;
    v = dataset + VPP * i + 2;
    
    if (*x >= 0 && *x < tile_size->width && *y >= 0 && *y < tile_size->height) {
      interpolated_bitmap[*y * tile_size->width + *x] = *v;
    }
  }
}

};  // namespace acid_maps

