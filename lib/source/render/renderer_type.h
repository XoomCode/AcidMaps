#ifndef LIB_SOURCE_RENDERER_RENDERER_TYPE_H_
#define LIB_SOURCE_RENDERER_RENDERER_TYPE_H_
/**
 * @file renderer_type.h
 * 
 * @date 2010-11-08
 * @authors Fabio R. Panettieri
 * @todo 
 */

namespace acid_maps {

/**
 * @brief List of available 
 */
enum RendererType {
  DENSE = 0,             /// Intervals are indexed
  SPARSE = 1,            /// Finds the right interval with a b-tree
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_RENDERER_RENDERER_TYPE_H_

