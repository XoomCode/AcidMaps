#ifndef LIB_SOURCE_ENCODE_ENCODER_H_
#define LIB_SOURCE_ENCODE_ENCODER_H_
/**
 * @file encode.h
 * @brief Encoder definition
 *
 * @date 2010-11-10
 * @authors Fabio R. Panettieri
 */

#include <cstddef>

namespace acid_maps {

/**
 * Forward declaration
 */
struct Size;

/**
 * @brief Renders the raw image
 */
class Encoder {
public:
    /**
     * @brief Virtual destructor allows proper destructor calls
     */
  virtual ~Encoder() {}
    /**
     * @todo brief
     */
  virtual void encode(Size* tile_size, unsigned char* rgba_buffer, unsigned char** output_buffer, size_t* output_size) = 0;
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_ENCODE_ENCODER_H_
