#ifndef LIB_SOURCE_CORE_BOUNDS_H_
#define LIB_SOURCE_CORE_BOUNDS_H_
/**
 * @file bounds.h
 * @brief Bounds structure implementation
 * 
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

namespace acid_maps {

/**
 * @brief Bounding Box representation
 * Instances of this class represent bounding boxes.
 * Data stored as left, bottom, right, top floats.
 * All values are initialized to 0, however, you should make sure you set them
 * before using the bounds for anything.
 */
struct Bounds {
  Bounds();
  Bounds(int min_x, int min_y, int max_x, int max_y);
  
  float min_x;
  float min_y;
  float max_x;
  float max_y;
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_CORE_BOUNDS_H_

