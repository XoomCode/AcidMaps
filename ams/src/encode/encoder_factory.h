#ifndef LIB_SOURCE_ENCODE_ENCODER_FACTORY_H_
#define LIB_SOURCE_ENCODE_ENCODER_FACTORY_H_
/**
 * @file encoder_factory.h
 * @brief Encoder factory definition
 * 
 * @date 2010-11-10
 * @authors Fabio R. Panettieri
 */

namespace acid_maps {

/**
 * @brief Class responsible of creating new encoders
 * Based on the Factory Method Pattern
 */
class EncoderFactory {
  public:
    /**
     * @brief Creates the expected encoder
     *
     * @param format int Encoder output format
     * @returns Encoder*
     */
    static Encoder* get(int format);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_ENCODE_ENCODER_FACTORY_H_

