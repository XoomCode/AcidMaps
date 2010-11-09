#include <cppunit/extensions/HelperMacros.h>
#include "../source/core/configuration.h"
#include "../source/constants/constants.h"
#include "../source/simplify/simplify_method.h"
#include "../source/interpolate/interpolation_strategy.h"
#include "../source/render/renderer_type.h"
#include "../source/acid_maps.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>

namespace ams = acid_maps;

class InterpolationsTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(InterpolationsTest);
  CPPUNIT_TEST( linearInterpolation );
  CPPUNIT_TEST_SUITE_END();
  
public:
  void setUp() {
    configuration = new ams::Configuration();
    configuration->dataset = create_dataset();
    configuration->dataset_size = 10;
    configuration->simplify_method = ams::COPY;
    configuration->simplify_size = 6;
    configuration->bounds = new ams::Bounds(-180, -90, 180, 90);
    configuration->tile_size = new ams::Size(1024, 512);
    configuration->intervals = create_intervals();
    configuration->intervals_colors = create_intervals_colors();
    configuration->intervals_size = 5;
    configuration->intervals_type = ams::SPARSE;
    output_buffer_size = 1024 * 512 * ams::RGBA;
    output_buffer = new unsigned char[output_buffer_size];
  }
  
  void linearInterpolation () {
    configuration->interpolation_strategy = ams::LINEAR;
    configuration->interpolation_parameter = 32;

    ams::generate(configuration, output_buffer);
    
    file = std::fopen("linear.ppm", "w");
    fwrite (output_buffer, output_buffer_size, sizeof(output_buffer), file);
    std::fclose(file);
  }
    
  void tearDown() {
    delete[] output_buffer;
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
  unsigned int output_buffer_size;
  std::FILE* file;
  
  float* create_dataset() {
    float* dataset = new float[10 * ams::VPP];
    for (int i = 0; i < 10; i++) {
      dataset[i * ams::VPP] = std::rand() % 360 - 180;
      dataset[i * ams::VPP + 1] = std::rand() % 180 - 90;
      dataset[i * ams::VPP + 2] = std::rand() % 150;
    }
    return dataset;
  }
  
  int* create_intervals() {
    int* intervals = new int[5];
    intervals[0] = 10;
    intervals[1] = 22;
    intervals[2] = 45;
    intervals[3] = 70;
    intervals[4] = 110;
    return intervals;
  }
  
  unsigned char* create_intervals_colors() {
    unsigned char* colors = new unsigned char[5 * ams::RGBA];
    colors[0] = 0x00; colors[1] = 0x00; colors[2] = 0x00; colors[3] = 0x00;
    colors[4] = 0xFF; colors[5] = 0x30; colors[6] = 0x30; colors[7] = 0x90;
    colors[8] = 0xFF; colors[9] = 0x90; colors[10] = 0x10; colors[11] = 0xB0;
    colors[12] = 0x00; colors[13] = 0xFF; colors[14] = 0x30; colors[15] = 0xFF;
    colors[16] = 0x00; colors[17] = 0x30; colors[18] = 0xFF; colors[19] = 0xFF;
    return colors; 
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION( InterpolationsTest );
