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
 * @brief Converts projected coordinates into  
 */
class Transformer {
  public:
    /**
     * @brief Transform each point geographic coordinates
     * in the dataset to pixel coordinates from the top-left corner of the image.
     */
    void transform(Configuration* configuration);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_TRANSFORM_TRANSFORMER_H_
