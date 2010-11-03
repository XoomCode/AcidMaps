/**
 * @file acid_maps.cc
 * @brief 
 *
 * @date 2010-11-02
 * @authors Fabio R. Panettieri
 * 
 * @todo Brief and description
 */

#include "./acid_maps.h"
#include "core/configuration.h"
#include "simplify/simplifier.h"
#include "simplify/simplifier_factory.h"
#include "transform/transformer.h"
#include "interpolate/interpolation.h"
#include "interpolate/interpolation_factory.h"
#include "interpolate/interpolation_strategy.h"

namespace acid_maps {

void generate(Configuration* configuration) {
  Simplifier* simplifier = SimplifierFactory::get(configuration->simplify_method);
  simplifier->simplify(configuration);
  
  Transformer* transformer = new Transformer();
  transformer->transform(configuration);
  
  Interpolation* interpolation = InterpolationFactory::get(configuration->interpolation_strategy);
  interpolation->interpolate(configuration);
  
  delete interpolation;
  delete transformer;
  delete simplifier;
}

};  // namespace acid_maps

