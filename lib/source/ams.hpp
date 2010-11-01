#ifndef __AMS_HPP__
#define __AMS_HPP__

#include "configuration.hpp"

namespace AcidMaps {
	
	/**
	 * Generates an interpolated image with the given configuration
	 */
	void interpolate(configuration cfg, uint32_t* out);

};

#endif

