/**
 * @file encoder_factory.cc
 * @brief Encoder factory implementation
 *
 * @date 2010-11-10
 * @authors Fabio R. Panettieri
 */
#include "./encoder.h"
#include "./encoder_factory.h"
#include "./encoding_format.h"
#include "png/png_encoder.h"

namespace acid_maps {

Encoder* EncoderFactory::get(int format) {
  switch (format) {
    case PNG:
      return new PngEncoder();
  }
}

};  // namespace acid_maps

