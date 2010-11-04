#ifndef LIB_SOURCE_INTERPOLATE_INTERPOLATION_H_
#define LIB_SOURCE_INTERPOLATE_INTERPOLATION_H_
/**
 * @file interpolation.h
 * @brief Interpolation base class
 *
 * It defines the interpolate method that must be implemented by all it's subclasses
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
 * @brief Interpolation's base class
 * 
 * You should not use this class directly.
 * Use InterpolationFactory if you want an instance of any subclass
 */
class Interpolation {
  public:
    /**
     * @brief Virtual destructor allows proper destructor calls
     */
    virtual ~Interpolation();

    /**
     * @brief Generates an interpolated int bitmap
     */
    virtual void interpolate(Configuration* configuration) = 0;
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_INTERPOLATE_INTERPOLATION_H_

