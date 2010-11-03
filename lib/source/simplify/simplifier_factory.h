/**
 * @file simplifier_factory.h
 * @brief Simplifier factory declaration
 * 
 * @date 2010-11-03
 * @authors Fabio R. Panettieri
 */

#ifndef LIB_SOURCE_SIMPLIFY_SIMPLIFIER_FACTORY_H_
#define LIB_SOURCE_SIMPLIFY_SIMPLIFIER_FACTORY_H_

namespace acid_maps {

/**
 * @brief Class responsible of creating new simplifiers
 * Based on the Factory Method Pattern
 */
class SimplifierFactory {
  public:
    /**
     * @brief Creates the requested Simplifier
     *
     * @param method SimplifyMethod Desired simplify method
     * @returns Simplifier*
     */
    static Simplifier* get(int method);
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_SIMPLIFY_SIMPLIFIER_FACTORY_H_

