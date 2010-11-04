#ifndef LIB_SOURCE_RENDER_RENDERER_FACTORY_H_
#define LIB_SOURCE_RENDER_RENDERER_FACTORY_H_
/**
 * @file renderer_factory.h
 * @brief Renderer factory declaration
 * 
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

namespace acid_maps {

/**
 * @brief Class responsible of creating new interpolations
 * Based on the Factory Method Pattern
 */
class RendererFactory {
  public:
    /**
     * @brief Creates the requested Renderer
     *
     * @param method int desired color depth
     * @returns Renderer*
     */
    static Renderer* get(int color_depth);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_RENDER_RENDERER_FACTORY_H_

