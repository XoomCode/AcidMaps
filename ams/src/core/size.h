#ifndef LIB_SOURCE_CORE_SIZE_H_
#define LIB_SOURCE_CORE_SIZE_H_
/**
 * @file size.h
 * @brief Size structure definition
 * 
 * @date 2010-11-05
 * @authors Fabio R. Panettieri
 */

namespace acid_maps {

/**
 * @brief Size representation
 */
struct Size {
  Size();
  Size(int width, int height);
  
  int width;
  int height;
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_CORE_SIZE_H_

