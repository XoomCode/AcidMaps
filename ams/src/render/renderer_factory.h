#ifndef LIB_SOURCE_RENDERER_RENDERER_FACTORY_H_
#define LIB_SOURCE_RENDERER_RENDERER_FACTORY_H_
/**
 * @file renderer_factory.h
 * @brief Renderer factory definition
 * 
 * @date 2010-11-08
 * @authors Fabio R. Panettieri
 */

namespace acid_maps {

/**
 * @brief Class responsible of creating new renderers
 * Based on the Factory Method Pattern
 */
class RendererFactory {
  public:
    /**
     * @brief Creates the expected renderer
     *
     * @param method int Expected renderer
     * @returns Renderer*
     */
    static Renderer* get(int type);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_RENDERER_RENDERER_FACTORY_H_

