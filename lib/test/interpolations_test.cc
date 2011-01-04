#include <cppunit/extensions/HelperMacros.h>
#include "../source/core/configuration.h"
#include "../source/constants/constants.h"
#include "../source/simplify/simplify_method.h"
#include "../source/interpolate/interpolation_strategy.h"
#include "../source/render/renderer_type.h"
#include "../source/encode/encoding_format.h"
#include "../source/acid_maps.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>

namespace ams = acid_maps;

class InterpolationsTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(InterpolationsTest);
  CPPUNIT_TEST(linearInterpolation);
//  CPPUNIT_TEST(nearestNeighborInterpolation);
  CPPUNIT_TEST_SUITE_END();
  
public:
  void setUp() {
    srand(time(0));
    configuration = new ams::Configuration();
    configuration->dataset = create_dataset();
    configuration->dataset_size = 100;
    configuration->simplify_method = ams::COPY;
    configuration->simplify_size = 100;
    configuration->bounds = new ams::Bounds(-180, -90, 180, 90);
    configuration->tile_size = new ams::Size(1024, 512);
    configuration->intervals_size = 5;
    configuration->intervals = create_intervals(configuration->intervals_size);
    configuration->intervals_colors = create_intervals_colors();
    configuration->intervals_type = ams::SPARSE;
    configuration->format = ams::PNG;
  }
  
  void linearInterpolation () {
    configuration->interpolation_strategy = ams::LINEAR;
    configuration->interpolation_parameter = 32;
    
    unsigned int output_size;
    ams::generate(configuration, &output_buffer, &output_size);

    file = std::fopen("linear.png", "wb");
    std::fwrite(output_buffer, sizeof(unsigned char), output_size, file);
    std::fclose(file);
  }
  
  void nearestNeighborInterpolation () {
    configuration->interpolation_strategy = ams::NEAREST_NEIGHBOR;
    
    unsigned int output_size;
    ams::generate(configuration, &output_buffer, &output_size);

    file = std::fopen("nearest.png", "wb");
    std::fwrite(output_buffer, sizeof(unsigned char), output_size, file);
    std::fclose(file);
  }
    
  void tearDown() {
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
  std::FILE* file;
  
  float* create_dataset() {
    float* dataset = new float[100 * ams::VPP];
    for (int i = 0; i < 100; i++) {
      dataset[i * ams::VPP] = std::rand() % 360 - 180;
      dataset[i * ams::VPP + 1] = std::rand() % 180 - 90;
      dataset[i * ams::VPP + 2] = std::rand() % 100;
    }
    return dataset;
  }
  
  int* create_intervals(int intervals_size) {
    int* intervals = new int[intervals_size];
    for (int i = 0; i < intervals_size; i++) {
      intervals[i] = (i + 1 ) * 20;
    }
    return intervals;
  }
  
  // ABGR!!
  unsigned char* create_intervals_colors() {
    unsigned char* colors = new unsigned char[5 * ams::RGBA];
    colors[0] = 0x00; colors[1] = 0x00; colors[2] = 0x00; colors[3] = 0x00;
    colors[4] = 0xFF; colors[5] = 0x00; colors[6] = 0x00; colors[7] = 0xFF;
    colors[8] = 0xFF; colors[9] = 0xFF; colors[10] = 0x00; colors[11] = 0xFF;
    colors[12] = 0x00; colors[13] = 0xFF; colors[14] = 0x00; colors[15] = 0xFF;
    colors[16] = 0x00; colors[17] = 0x00; colors[18] = 0xFF; colors[19] = 0xFF;
    return colors; 
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION( InterpolationsTest );
