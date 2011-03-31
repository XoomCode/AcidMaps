#include <cppunit/extensions/HelperMacros.h>
#include "../src/core/configuration.h"
#include "../src/core/color.h"
#include "../src/constants/constants.h"
#include "../src/simplify/simplify_method.h"
#include "../src/interpolate/interpolation_strategy.h"
#include "../src/render/renderer_type.h"
#include "../src/encode/encoding_format.h"
#include "../src/acid_maps.h"

#include <cstring>
#include <cstdlib>
#include <ctime>

namespace ams = acid_maps;

#define DATASET_SIZE 100
#define SIMPLIFY_SIZE 75

class InterpolationsTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(InterpolationsTest);
  CPPUNIT_TEST(dummyInterpolation);
  CPPUNIT_TEST(linearInterpolation);
  CPPUNIT_TEST(nearestNeighborInterpolation);
  CPPUNIT_TEST(inverseDistanceWeightingInterpolation);
  CPPUNIT_TEST_SUITE_END();
  
public:
  void setUp() {
    srand(time(NULL));
    configuration = new ams::Configuration();
    configuration->dataset = create_dataset();
    configuration->dataset_size = DATASET_SIZE;
    configuration->simplify_size = SIMPLIFY_SIZE;
    configuration->simplify_method = ams::COPY;
    configuration->bounds = new ams::Bounds(-180, -90, 180, 90);
    configuration->tile_size = new ams::Size(1024, 512);
    configuration->intervals_size = 5;
    configuration->intervals = create_intervals(configuration->intervals_size);
    configuration->intervals_colors = create_intervals_colors();
    configuration->renderer_type = ams::GRADIENT;

    configuration->format = ams::RAW;
  }
  
  void dummyInterpolation () {
    configuration->interpolation_strategy = ams::DUMMY;
    configuration->radius = 32;
    ams::generate(configuration, &output_buffer, &output_size);
    file = std::fopen("dummy.png", "wb");
  }
  
  void linearInterpolation () {
    configuration->interpolation_strategy = ams::LINEAR;
    configuration->radius = 64;
    ams::generate(configuration, &output_buffer, &output_size);
    file = std::fopen("linear.png", "wb");
  }
  
  void nearestNeighborInterpolation () {
    configuration->interpolation_strategy = ams::NEAREST_NEIGHBOR;
    ams::generate(configuration, &output_buffer, &output_size);
    file = std::fopen("nearest.png", "wb");
  }
  
  void inverseDistanceWeightingInterpolation () {
    configuration->interpolation_strategy = ams::INVERSE_DISTANCE_WEIGHTING;
    ams::generate(configuration, &output_buffer, &output_size);
    file = std::fopen("idw.png", "wb");
  }
    
  void tearDown() {
    std::fwrite(output_buffer, sizeof(unsigned char), output_size, file);
    std::fclose(file);
    free(output_buffer);
    delete[] configuration->intervals_colors;
    delete[] configuration->intervals;
    delete configuration->tile_size;
    delete configuration->bounds;
    delete[] configuration->dataset;
    delete configuration;
  }

private:
  ams::Configuration* configuration;
  unsigned char* output_buffer;
  unsigned int output_size;
  std::FILE* file;
  
  ams::Point* create_dataset() {
    ams::Point* dataset = new ams::Point[DATASET_SIZE];
    ams::Point* point;
    for (int i = 0; i < DATASET_SIZE; i++) {
      point = dataset + i;
      point->x = std::rand() % 360 - 180;
      point->y = std::rand() % 180 - 90;
      point->value = std::rand() % 100;
    }
    return dataset;
  }
  
  float* create_intervals(int intervals_size) {
    float* intervals = new float[intervals_size];
    std::memset(intervals, 0, intervals_size * sizeof(intervals));
    
    for (int i = 0; i < intervals_size; i++) {
      intervals[i] = (i + 1 ) * 20;
    }
    return intervals;
  }
  
  ams::Color* create_intervals_colors() {
    ams::Color* color;
    ams::Color* colors = new ams::Color[5];
    
    color = colors;
    color->r = 0x20; color->g = 0x20; color->b = 0x20; color->a = 0xFF;
    
    color = colors + 1;
    color->r = 0xFF; color->g = 0x00; color->b = 0x00; color->a = 0xFF;
    
    color = colors + 2;
    color->r = 0xFF; color->g = 0xFF; color->b = 0x00; color->a = 0xFF;
    
    color = colors + 3;
    color->r = 0x00; color->g = 0xFF; color->b = 0x00; color->a = 0xFF;
    
    color = colors + 4;
    color->r = 0x00; color->g = 0x00; color->b = 0xFF; color->a = 0xFF;
    return colors; 
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION( InterpolationsTest );
