#ifndef LIB_SOURCE_INTERPOLATE_INTERPOLATION_FACTORY_H_
#define LIB_SOURCE_INTERPOLATE_INTERPOLATION_FACTORY_H_
/**
 * @file interpolation_factory.h
 * @brief Interpolation factory declaration
 * 
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

namespace acid_maps {

/**
 * @brief Class responsible of creating new interpolations
 * Based on the Factory Method Pattern
 */
class InterpolationFactory {
  public:
    /**
     * @brief Creates the requested Interpolation
     *
     * @param method int Expected interpolation
     * @returns Interpolation*
     */
    static Interpolation* get(int strategy);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_INTERPOLATE_INTERPOLATION_FACTORY_H_

