#include <cppunit/extensions/HelperMacros.h>
#include "../../source/core/configuration.h"
#include "../../source/core/bounds.h"
#include "../../source/core/point.h"
#include "../../source/core/pixel.h"
#include "../../source/core/size.h"
#include "../../source/transform/transformer.h"

class TransformerTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(TransformerTest);
  CPPUNIT_TEST( singlePointDataset );
  CPPUNIT_TEST( multiPointDataset );
  CPPUNIT_TEST( emptyDataset );
  CPPUNIT_TEST_SUITE_END();
  
public:
  void setUp() {
    configuration = new acid_maps::Configuration();
    configuration->bounds = new acid_maps::Bounds(-180, -90, 180, 90);
    configuration->tile_size = new acid_maps::Size(512, 512);
    
    transformer = new acid_maps::Transformer();
  }
  
  void tearDown() {
    delete configuration->tile_size;
    delete configuration->bounds;
    delete configuration;
  
    delete transformer;
  }
  
  void singlePointDataset () {
    acid_maps::Point* dataset = new acid_maps::Point[1];
    dataset->x = 90.0;
    dataset->y = 45.0;
    dataset->value = 200;
    
    configuration->dataset_size = 1;
    configuration->dataset = dataset;
    
    acid_maps::Pixel* transformed_dataset = new acid_maps::Pixel[1];
    transformer->transform(configuration->bounds, configuration->tile_size, dataset, 1, transformed_dataset);
    
    CPPUNIT_ASSERT_EQUAL(transformed_dataset[0].x, configuration->tile_size->width / 4 * 3);
    CPPUNIT_ASSERT_EQUAL(transformed_dataset[0].y, configuration->tile_size->height / 4);
    CPPUNIT_ASSERT_EQUAL(transformed_dataset[0].value, dataset[0].value);
    
    delete[] transformed_dataset;
    delete[] dataset; 
  }
  
  void multiPointDataset () {
    acid_maps::Point* dataset = new acid_maps::Point[4];
    acid_maps::Point* point;
    
    point = dataset;
    point->x = 90.0;
    point->y = 45.0;
    point->value = 200;
    
    point = dataset + 1;
    point->x = -90.0;
    point->y = 45.0;
    point->value = 100;
    
    point = dataset + 2;
    point->x = 90.0;
    point->y = -45.0;
    point->value = 50;
    
    point = dataset + 3;
    point->x = -90.0;
    point->y = -45.0;
    point->value = 260;
    
    configuration->dataset_size = 4;
    configuration->dataset = dataset;
    
    acid_maps::Pixel* transformed_dataset = new acid_maps::Pixel[4];
    transformer->transform(configuration->bounds, configuration->tile_size, dataset, 4, transformed_dataset);
    
    CPPUNIT_ASSERT_EQUAL(transformed_dataset[0].x, configuration->tile_size->width / 4 * 3);
    CPPUNIT_ASSERT_EQUAL(transformed_dataset[0].y, configuration->tile_size->height / 4);
    
    CPPUNIT_ASSERT_EQUAL(transformed_dataset[1].x, configuration->tile_size->width / 4);
    CPPUNIT_ASSERT_EQUAL(transformed_dataset[1].y, configuration->tile_size->height / 4);
    
    CPPUNIT_ASSERT_EQUAL(transformed_dataset[2].x, configuration->tile_size->width / 4 * 3);
    CPPUNIT_ASSERT_EQUAL(transformed_dataset[2].y, configuration->tile_size->height / 4 * 3);
    
    CPPUNIT_ASSERT_EQUAL(transformed_dataset[3].x, configuration->tile_size->width / 4);
    CPPUNIT_ASSERT_EQUAL(transformed_dataset[3].y, configuration->tile_size->height / 4 * 3);
    
    delete[] transformed_dataset;
    delete[] dataset; 
  }
  
  void emptyDataset () {
    acid_maps::Point* dataset = new acid_maps::Point[0];
    
    configuration->dataset_size = 0;
    configuration->dataset = dataset;
    
    acid_maps::Pixel* transformed_dataset = new acid_maps::Pixel[0];
    transformer->transform(configuration->bounds, configuration->tile_size, dataset, 0, transformed_dataset);
    
    delete[] transformed_dataset;
    delete[] dataset; 
  }

private:
  acid_maps::Configuration* configuration;
  acid_maps::Transformer* transformer;
};

CPPUNIT_TEST_SUITE_REGISTRATION( TransformerTest );
