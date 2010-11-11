#ifndef LIB_SOURCE_ENCODE_PNG_ENCODER_H_
#define LIB_SOURCE_ENCODE_PNG_ENCODER_H_
/**
 * @file png_encoder.h
 * @brief Png encoder implementation
 *
 * Generates a png with the given image
 *
 * @date 2010-11-10
 * @authors Fabio R. Panettieri
 */

#include "../encoder.h"

namespace acid_maps {

/**
 * @brief Keeps the dataset untouched
 */
class PngEncoder : public Encoder {
  /**
   */
  void encode(Size* tile_size, const unsigned char* rgba_buffer, unsigned char* output_buffer, std::size_t* output_size);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_ENCODE_PNG_ENCODER_H_

