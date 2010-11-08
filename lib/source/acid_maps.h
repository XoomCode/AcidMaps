#ifndef LIB_SOURCE_ACID_MAPS_H_
#define LIB_SOURCE_ACID_MAPS_H_
/** 
 * @mainpage Acid Maps core library
 * 
 * @file acid_maps.h
 * @brief Acid Maps public interface
 *
 * Acid Maps images are generated through the following method
 *
 * Simplify -> Transform -> Interpolate -> Render
 * 
 * Simplify: Acid Maps can interpolate very large datasets.
 * In order to keep the proccess stable and fast execution times, its very important to 
 * simplify them to smaller sizes.
 * This proccess generates simplified datasets.
 * 
 * Transform: Datasets contains projected information.
 * In order to improve the interpolation proccess and allow a proper rendering
 * they are transformed to pixels coordinates from the top-left corner of the image.
 *
 * Interpolate: In order to generate raster images from a discrete set of points
 * missing values are generated through different interpolation strategy.
 *
 * Render: After the interpolated bitmap has been generated, the renderer generates
 * an image that represents that bitmap
 *
 * @date 2010-11-02
 * @authors Fabio R. Panettieri
 */

namespace acid_maps {

/**
 * Configuration forward declaration
 */ 
struct Configuration;

/**
 * @brief Generates an interpolated raster with the given configuration
 *
 * This is Acid Maps public interface
 * Generates a raw raster image based on the given configuration.
 *
 * @param configuration Configuration 
 * @param output_buffer char* a 32bits raw image will stored here
 */
void generate(Configuration* configuration, unsigned char output_buffer[]);

};  // namespace acid_maps

#endif  // LIB_SOURCE_ACID_MAPS_H_

