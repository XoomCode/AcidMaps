#ifndef LIB_SOURCE_RENDER_RENDERER_H_
#define LIB_SOURCE_RENDER_RENDERER_H_
/**
 * @file transformer.h
 * @brief Transformer definition
 *
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

namespace acid_maps {

/**
 * Forward declaration
 */
struct Configuration;

/**
 * @brief Renders the raw image
 */
class Renderer {
  public:
     /**
     * @brief Virtual destructor allows proper destructor calls
     */
    virtual ~Renderer();

    /**
     * @brief After the interpolated bitmap has been generated, the renderer generates
     * an image that represents that bitmap
     */
    virtual void render(Configuration* configuration) = 0;
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_RENDER_RENDERER_H_
