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
#include "core/configuration.h"
#include "simplify/simplifier.h"
#include "simplify/simplifier_factory.h"
#include "transform/transformer.h"

namespace acid_maps {

/// Number of values per point
static const int XYV = 3;

void generate(Configuration configuration, char* output_buffer) {
  Simplifier* simplifier = SimplifierFactory::get(configuration.simplify_method);
  simplifier->simplify(configuration);
  
  Transformer* transformer = new Transformer();
  transformer->transform(configuration);
  
  delete transformer;
  delete simplifier;
}

};  // namespace acid_maps

