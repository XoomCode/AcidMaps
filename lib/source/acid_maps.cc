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
#include "render/renderer.h"
#include "render/renderer_factory.h"

namespace acid_maps {

void generate(Configuration* configuration) {
  Simplifier* simplifier = SimplifierFactory::get(configuration->simplify_method);
  simplifier->simplify(configuration);
  delete simplifier;
  
  Transformer* transformer = new Transformer();
  transformer->transform(configuration);
  delete transformer;
  
  Interpolation* interpolation = InterpolationFactory::get(configuration->interpolation_strategy);
  interpolation->interpolate(configuration);
  delete interpolation;
  
  Renderer* renderer = RendererFactory::get(configuration->color_depth);
  renderer->render(configuration);
  delete renderer;
}

};  // namespace acid_maps

