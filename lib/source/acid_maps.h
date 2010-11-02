#ifndef LIB_SOURCE_ACID_MAPS_H_
#define LIB_SOURCE_ACID_MAPS_H_

/** 
 * @mainpage Acid Maps core library
 * 
 * @file acid_maps.h
 * @brief la
 *
 * @date 2010-11-02
 * @authors Fabio R. Panettieri
 * 
 * @todo Brief and description
 * 
 */

namespace acid_maps {

struct Configuration;

  /**
   * @brief Generates an interpolated raster with the given configuration
   *
   * @param configuration Configuration
   * @param output_buffer char*
   * 
   * @todo More documentation
   */
  void interpolate(Configuration configuration, char* output_buffer);

};  // namespace acid_maps

#endif  // LIB_SOURCE_ACID_MAPS_H_

