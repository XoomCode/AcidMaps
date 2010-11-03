/**
 * @file acid_maps.cc
 * @brief 
 *
 * @date 2010-11-02
 * @authors Fabio R. Panettieri
 * 
 * @todo Brief and description
 * 
 */

#include "./acid_maps.h"
#include "./configuration.h"
#include "simplify/simplifier.h"
#include "simplify/simplifier_factory.h"

namespace acid_maps {

void generate(Configuration configuration, char* output_buffer) {
  Simplifier* simplifier = SimplifierFactory::get(configuration.simplify_method);
  simplifier->simplify(configuration);

  delete simplifier;
}

};  // namespace acid_maps

