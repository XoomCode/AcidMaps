/**
 * @file png_encoder.cc
 * @brief Png Encoder implementation
 *
 * @date 2010-11-10
 * @authors Fabio R. Panettieri
 */

#include "../../constants/constants.h"
#include "../../core/size.h"
#include "./png_encoder.h"
#include "lodepng.h"

#include <cstring>

namespace acid_maps {

void PngEncoder::encode(Size* tile_size, const unsigned char* rgba_buffer, unsigned char* output_buffer, unsigned int* output_size) {
  LodePNG_encode32(&output_buffer, output_size, rgba_buffer, tile_size->width, tile_size->height);
}

};  // namespace acid_maps

