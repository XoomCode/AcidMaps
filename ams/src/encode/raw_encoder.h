#ifndef LIB_SOURCE_ENCODE_RAW_ENCODER_H_
#define LIB_SOURCE_ENCODE_RAW_ENCODER_H_
/**
 * @file raw_encoder.h
 * @brief Raw encoder implementation
 *
 * Generates a raw RGBA8888 image
 *
 * @date 2011-03-31
 * @authors Fabio R. Panettieri
 */
 
#include "./encoder.h"

namespace acid_maps {

/**
 * Size forward declaration
 */ 
struct Size;

/**
 * @brief
 */
class RawEncoder : public Encoder {
  /**
   */
  void encode(Size* tile_size, unsigned char* rgba_buffer, unsigned char** output_buffer, unsigned int* output_size);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_ENCODE_RAW_ENCODER_H_

