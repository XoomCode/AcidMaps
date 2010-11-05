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
#include "constants/constants.h"
#include "core/configuration.h"
#include "simplify/simplifier.h"
#include "simplify/simplifier_factory.h"
#include "transform/transformer.h"
#include "interpolate/interpolation.h"
#include "interpolate/interpolation_factory.h"
#include "render/renderer.h"

namespace acid_maps {

void generate(Configuration* configuration, unsigned char* output_buffer) {
  float* simplified_dataset = new float[configuration->simplify_size * VPP];
  Simplifier* simplifier = SimplifierFactory::get(configuration->simplify_method);

  simplifier->simplify(configuration->dataset, configuration->dataset_size,
    configuration->simplify_size, simplified_dataset);
  
  delete simplifier;
  
  int* transformed_dataset = new int[configuration->simplify_size * VPP];
  Transformer* transformer = new Transformer();

  transformer->transform(configuration->bounds, configuration->tile_size,
    simplified_dataset, configuration->simplify_size, transformed_dataset);
    
  delete transformer;
  delete[] simplified_dataset;
  
  int* interpolated_bitmap = new int[configuration->tile_size->width * configuration->tile_size->height];
  Interpolation* interpolation = InterpolationFactory::get(configuration->interpolation_strategy);
  
  interpolation->interpolate(configuration->tile_size, transformed_dataset, 
    configuration->simplify_size, interpolated_bitmap);
  
  delete interpolation;
  delete[] transformed_dataset;
  
  Renderer* renderer = new Renderer();
  renderer->render(configuration->tile_size, interpolated_bitmap, output_buffer);
  delete renderer;
  delete[] interpolated_bitmap;
}

};  // namespace acid_maps

