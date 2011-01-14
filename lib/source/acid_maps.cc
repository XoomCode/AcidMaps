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

#define PROFILE_

#ifdef PROFILE
#include <cstdio>
#include <ctime>
#endif

namespace acid_maps {

void generate(Configuration* configuration, unsigned char** output_buffer, unsigned int* output_size) {

#ifdef PROFILE
  float begin, end, full_begin, full_end;
#endif
#ifdef PROFILE
  begin = std::clock();
  std::printf("begin: %8.4f\n", begin / CLOCKS_PER_SEC);
  full_begin = begin;
#endif
  Point* simplified_dataset = new Point[configuration->simplify_size];
  Simplifier* simplifier = SimplifierFactory::get(configuration->simplify_method);
  simplifier->simplify(configuration->dataset, configuration->dataset_size,
    configuration->simplify_size, simplified_dataset);
  delete simplifier;
#ifdef PROFILE
  end = std::clock();
  std::printf("simplify: %8.4f\n", (end - begin) / CLOCKS_PER_SEC);
#endif

#ifdef PROFILE
  begin = std::clock();
#endif
  Pixel* transformed_dataset = new Pixel[configuration->simplify_size];
  Transformer* transformer = new Transformer();
  transformer->transform(configuration->bounds, configuration->tile_size,
    simplified_dataset, configuration->simplify_size, transformed_dataset);
  delete transformer;
  delete[] simplified_dataset;
#ifdef PROFILE
  end = std::clock();
  std::printf("transform: %8.4f\n", (end - begin) / CLOCKS_PER_SEC);
#endif

#ifdef PROFILE
  begin = std::clock();
#endif
  int buffer_size = configuration->tile_size->width * configuration->tile_size->height;
  float* interpolated_bitmap = new float[buffer_size];
  Interpolation* interpolation = InterpolationFactory::get(configuration->interpolation_strategy);
  interpolation->interpolate(configuration->tile_size, transformed_dataset, configuration->simplify_size, 
    configuration->interpolation_parameter, interpolated_bitmap);
  delete interpolation;
  delete[] transformed_dataset;
#ifdef PROFILE
  end = std::clock();
  std::printf("interpolate: %8.4f\n", (end - begin) /  CLOCKS_PER_SEC);
#endif

#ifdef PROFILE
  begin = std::clock();
#endif
  unsigned char* rgba_buffer = new unsigned char[buffer_size * RGBA];
  Renderer* renderer = RendererFactory::get(configuration->intervals_type);
  renderer->render(interpolated_bitmap, configuration->tile_size, configuration->intervals, 
    configuration->intervals_size, configuration->intervals_colors, rgba_buffer);
  delete renderer;
  delete[] interpolated_bitmap;
#ifdef PROFILE
  end = std::clock();
  std::printf("render: %8.4f\n", (end - begin) /  CLOCKS_PER_SEC);
#endif

#ifdef PROFILE
  begin = std::clock();
#endif
  Encoder* encoder = EncoderFactory::get(configuration->format);
  encoder->encode(configuration->tile_size, rgba_buffer, output_buffer, output_size);
  delete encoder;
  delete[] rgba_buffer;
#ifdef PROFILE
  end = std::clock();
  std::printf("encode: %8.4f\n", (end - begin) / CLOCKS_PER_SEC);
  
  full_end = end;
  std::printf("total: %8.4f\n", (full_end - full_begin) / CLOCKS_PER_SEC);
#endif
}

};  // namespace acid_maps

