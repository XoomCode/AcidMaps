#include <cppunit/extensions/HelperMacros.h>
#include "../../source/constants/constants.h"
#include "../../source/core/size.h"
#include "../../source/core/pixel.h"
#include "../../source/interpolate/interpolation.h"
#include "../../source/interpolate/dummy_interpolation.h"

class DummyInterpolationTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(DummyInterpolationTest);
  CPPUNIT_TEST( singlePointTest );
  CPPUNIT_TEST( multiPointTest );
  CPPUNIT_TEST( emptyPointTest );
  CPPUNIT_TEST_SUITE_END();
  
public:
  void setUp() {
    interpolation = new acid_maps::DummyInterpolation();
    size = new acid_maps::Size(512, 512);
    interpolated_bitmap = new float[size->width * size->height];
  }
  
  void tearDown() {
    delete[] interpolated_bitmap;
    delete size;
    delete interpolation;
  }
  
  void singlePointTest () {
    acid_maps::Pixel* dataset = new acid_maps::Pixel[1];
    dataset->x = 10;
    dataset->y = 10;
    dataset->value = 200;
    
    interpolation->interpolate(size, dataset, 1, 0, interpolated_bitmap);
    
    CPPUNIT_ASSERT_EQUAL(interpolated_bitmap[5130], 200.0f);
    
    delete[] dataset;
  }
  
  void multiPointTest () {
    acid_maps::Pixel* dataset = new acid_maps::Pixel[4];
    acid_maps::Pixel* pixel;
    
    pixel = dataset;
    pixel->x = 128;
    pixel->y = 17;
    pixel->value = 200;
    
    pixel = dataset + 1;
    pixel->x = 11;
    pixel->y = 10;
    pixel->value = 100;
    
    pixel = dataset + 2;
    pixel->x = 511;
    pixel->y = 511;
    pixel->value = 50;
    
    pixel = dataset + 3;
    pixel->x = 320;
    pixel->y = 20;
    pixel->value = 260;
    
    interpolation->interpolate(size, dataset, 4, 0, interpolated_bitmap);
    
    CPPUNIT_ASSERT_EQUAL(interpolated_bitmap[8832], 200.0f);
    CPPUNIT_ASSERT_EQUAL(interpolated_bitmap[5131], 100.0f);
    CPPUNIT_ASSERT_EQUAL(interpolated_bitmap[262143], 50.0f);
    CPPUNIT_ASSERT_EQUAL(interpolated_bitmap[10560], 260.0f);
    
    delete[] dataset;
  }
  
  void emptyPointTest () {
    acid_maps::Pixel* dataset = new acid_maps::Pixel[0];
    
    interpolation->interpolate(size, dataset, 0, 0, interpolated_bitmap);
    
    delete[] dataset;
  }

private:
  acid_maps::Interpolation* interpolation;
  acid_maps::Pixel* dataset;
  float* interpolated_bitmap;
  acid_maps::Size* size;
};

CPPUNIT_TEST_SUITE_REGISTRATION( DummyInterpolationTest );
