#ifndef LIB_SOURCE_TRANSFORM_TRANSFORMER_H_
#define LIB_SOURCE_TRANSFORM_TRANSFORMER_H_
/**
 * @file transformer.h
 * @brief Transformer definition
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

namespace acid_maps {

/**
 * Forward declarations
 */ 
struct Point;
struct Pixel;

class Transformer {
  public:
    /**
     * @brief Transform each point geographic coordinates
     * in the dataset to pixel coordinates from the top-left corner of the image.
     *
     *  * The configuration parameter contains a dataset member that is an array of Valued Points (VP).
     * Each VP is actually a set of 3 floats:
     *   x: Horizontal position of the point in a geographic Spatial Reference System (SRS)
     *   y: Vertical position of the point in a SRS
     *   v: Value or Weight of that point
     *
     * In order to interpolate and render our dataset, we need to convert
     * those points to a more screen friendly coordinate system.
     * Thus, points coordinates are transformed into pixel distance from the top left corner of the pixel
     *
     *       WORLD              0,0    px
     *   |------------|        |-----------|
     *   |     |---o x,y       |      |    |
     *   |     |   |  |        |      |    |
     *   |------------|  --->  |      |    |
     *   |     |0,0   |        |------o px,py
     *   |     |      |        |           |
     *   |------------|        |-----------|
     *                              TILE
     */
    void transform(Bounds* bounds, Size* tile_size, Point* dataset, int dataset_size, Pixel* transformed_dataset);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_TRANSFORM_TRANSFORMER_H_
