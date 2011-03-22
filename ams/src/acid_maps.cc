/**
 * @file acid_maps.cc
 * @brief 
 *
 * @date 2010-11-02
 * @authors Fabio R. Panettieri
 * 
 * @todo Brief and description
 */

#include "constants/constants.h"
#include "core/configuration.h"
#include "core/pixel.h"
#include "core/validator.h"
#include "simplify/simplifier.h"
#include "simplify/simplifier_factory.h"
#include "transform/transformer.h"
#include "interpolate/interpolation.h"
#include "interpolate/interpolation_factory.h"
#include "render/renderer.h"
#include "render/renderer_factory.h"
#include "encode/encoder.h"
#include "encode/encoder_factory.h"
#include "./acid_maps.h"

namespace acid_maps {

int generate(Configuration* configuration, unsigned char** output_buffer, size_t* output_size) {
	Validator validator;
	int error = validator.validate(configuration);
	if(error) return error;
	
  Point* simplified_dataset = new Point[configuration->simplify_size];
  Simplifier* simplifier = SimplifierFactory::get(configuration->simplify_method);
  simplifier->simplify(configuration->dataset, configuration->dataset_size,
    simplified_dataset, configuration->simplify_size);
  delete simplifier;
  
  Pixel* transformed_dataset = new Pixel[configuration->simplify_size];
  Transformer* transformer = new Transformer();
  transformer->transform(configuration->bounds, configuration->tile_size,
    simplified_dataset, configuration->simplify_size, transformed_dataset);
  delete transformer;
  delete[] simplified_dataset;
  
  int buffer_size = configuration->tile_size->width * configuration->tile_size->height;
  float* interpolated_bitmap = new float[buffer_size];
  Interpolation* interpolation = InterpolationFactory::get(configuration->interpolation_strategy);
  interpolation->interpolate(configuration->tile_size, transformed_dataset, configuration->simplify_size, 
    configuration->radius, interpolated_bitmap);
  delete interpolation;
  delete[] transformed_dataset;
  
  unsigned char* rgba_buffer = new unsigned char[buffer_size * RGBA];
  Renderer* renderer = RendererFactory::get(configuration->renderer_type);
  renderer->render(interpolated_bitmap, configuration->tile_size, configuration->intervals, 
    configuration->intervals_size, configuration->intervals_colors, rgba_buffer);
  delete renderer;
  delete[] interpolated_bitmap;
  
  Encoder* encoder = EncoderFactory::get(configuration->format);
  encoder->encode(configuration->tile_size, rgba_buffer, output_buffer, output_size);
  delete encoder;
  delete[] rgba_buffer;
  
  return 0;
}

};  // namespace acid_maps

