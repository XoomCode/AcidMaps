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

void PngEncoder::encode(Size* tile_size, unsigned char* rgba_buffer, unsigned char* output_buffer, unsigned int* output_size) {
  LodePNG_Encoder encoder;
  LodePNG_Encoder_init(&encoder);
  LodePNG_Encoder_encode(&encoder, &output_buffer, output_size, rgba_buffer, tile_size->width, tile_size->height);
  LodePNG_Encoder_cleanup(&encoder);
}

};  // namespace acid_maps

