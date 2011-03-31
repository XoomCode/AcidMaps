/**
 * @file png_encoder.cc
 * @brief Png Encoder implementation
 *
 * @date 2010-11-10
 * @authors Fabio R. Panettieri
 */

#include "./png_encoder.h"

#include "lodepng.h"
#include "../../core/size.h"

namespace acid_maps {

void PngEncoder::encode(Size* tile_size, unsigned char* rgba_buffer, unsigned char** output_buffer, unsigned int* output_size) {
  size_t size;
  LodePNG_encode32(output_buffer, &size, rgba_buffer, tile_size->width, tile_size->height);
  *output_size = size;
}

};  // namespace acid_maps

