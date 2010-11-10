#ifndef LIB_SOURCE_CORE_RECTANGLE_H_
#define LIB_SOURCE_CORE_RECTANGLE_H_
/**
 * @file rectangle.h
 * @brief Rectangle structure definition
 * 
 * @date 2010-11-09
 * @authors Fabio R. Panettieri
 */

namespace acid_maps {

/**
 * @brief Size representation
 */
class Rectangle {
public:
  Rectangle();
  Rectangle(int min_x, int min_y, int max_x, int max_y);
  void resize(int min_x, int min_y, int max_x, int max_y);
  void intersect(int min_x, int min_y, int max_x, int max_y);

  int min_x;
  int min_y;
  int max_x;
  int max_y;
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_CORE_RECTANGLE_H_

