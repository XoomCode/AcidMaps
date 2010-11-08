#include <cppunit/extensions/HelperMacros.h>
#include "../../source/constants/constants.h"
#include "../../source/core/size.h"
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
    interpolated_bitmap = new int[size->width * size->height];
  }
  
  void tearDown() {
    delete[] interpolated_bitmap;
    delete size;
    delete interpolation;
  }
  
  void singlePointTest () {
    int* dataset = create_dataset(1);
    dataset[0] = 10;
    dataset[1] = 10;
    dataset[2] = 200;
    
    interpolation->interpolate(size, dataset, 1, interpolated_bitmap);
    
    CPPUNIT_ASSERT_EQUAL(interpolated_bitmap[5130], 200);
    
    delete[] dataset;
  }
  
  void multiPointTest () {
    int* dataset = create_dataset(4);
    dataset[0] = 128;
    dataset[1] = 17;
    dataset[2] = 200;
    
    dataset[3] = 11;
    dataset[4] = 10;
    dataset[5] = 100;
    
    dataset[6] = 511;
    dataset[7] = 511;
    dataset[8] = 50;
    
    dataset[9] = 320;
    dataset[10] = 20;
    dataset[11] = 260;
    
    interpolation->interpolate(size, dataset, 4, interpolated_bitmap);
    
    CPPUNIT_ASSERT_EQUAL(interpolated_bitmap[8832], 200);
    CPPUNIT_ASSERT_EQUAL(interpolated_bitmap[5131], 100);
    CPPUNIT_ASSERT_EQUAL(interpolated_bitmap[262143], 50);
    CPPUNIT_ASSERT_EQUAL(interpolated_bitmap[10560], 260);
    
    delete[] dataset;
  }
  
  void emptyPointTest () {
    int* dataset = create_dataset(0);
    
    interpolation->interpolate(size, dataset, 0, interpolated_bitmap);
    
    delete[] dataset;
  }

private:
  acid_maps::Interpolation* interpolation;
  int* dataset;
  int* interpolated_bitmap;
  acid_maps::Size* size;
  
  int* create_dataset(int size) {
    return new int[size * acid_maps::VPP];
  }
  
};

CPPUNIT_TEST_SUITE_REGISTRATION( DummyInterpolationTest );
