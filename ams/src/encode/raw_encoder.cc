/**
 * @file raw_encoder.cc
 * @brief Raw Encoder implementation
 *
 * @date 2011-03-31
 * @authors Fabio R. Panettieri
 */

#include "./raw_encoder.h"

#include <cstdlib>
#include <cstring>

#include "../core/size.h"

namespace acid_maps {

void RawEncoder::encode(Size* tile_size, unsigned char* rgba_buffer, unsigned char** output_buffer, unsigned int* output_size) {
  
  // We allocate 4 bytes for each pixel
  size_t size = tile_size->width * tile_size->height * 4;
  *output_buffer = (unsigned char*) std::malloc(size);
  std::memcpy(*output_buffer, rgba_buffer, size);
  *output_size = size;
  
}

};  // namespace acid_maps

