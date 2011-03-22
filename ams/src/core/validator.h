#ifndef LIB_SOURCE_CORE_VALIDATOR_H_
#define LIB_SOURCE_CORE_VALIDATOR_H_
/**
 * @file validator.h
 * @brief Validates the configuration
 * 
 * @date 2011-03-04
 * @authors Fabio R. Panettieri
 */

namespace acid_maps {

/**
 * Configuration forward declaration
 */ 
struct Configuration;

class Validator {

public:
	int validate(Configuration* configuration);
	
};

};  // namespace acid_maps

#endif  // LIB_SOURCE_CORE_VALIDATOR_H_

