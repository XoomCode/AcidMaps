/**
 * @file acid_maps.cc
 * @brief 
 *
 * @date 2010-11-02
 * @authors Fabio R. Panettieri
 * 
 * @todo Brief and description
 * 
 */
#include "./acid_maps.h"
#include "./configuration.h"

namespace acid_maps {

void interpolate(Configuration configuration, char* output_buffer) {
  for (int i = 0; i < configuration.output_buffer_length; i++) {
    output_buffer[i] = '6';
  }
}

};  // namespace acid_maps

