#ifndef LIB_SOURCE_SIMPLIFY_SIMPLIFIER_H_
#define LIB_SOURCE_SIMPLIFY_SIMPLIFIER_H_
/**
 * @file simplifier.h
 * @brief Simplifiers base class
 *
 * It defines the simplify method that must be implemented by all it's subclasses
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
 * @brief Simplifier's base class
 * 
 * You should not use this class directly.
 * Use SimplifierFactory if you want an instance of any subclass
 */
class Simplifier {
  public:
	Simplifier();
    /**
     * @brief Virtual destructor allows proper destructor calls
     */
    virtual ~Simplifier(){};

    /**
     * @brief Reduce the number of valued points
     */
    virtual void simplify(Configuration* configuration) = 0;
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_SIMPLIFY_SIMPLIFIER_H_

