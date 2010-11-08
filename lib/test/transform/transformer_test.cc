#include <cppunit/extensions/HelperMacros.h>
#include "../../../lib/source/core/configuration.h"
#include "../../../lib/source/core/bounds.h"
#include "../../../lib/source/core/size.h"
#include "../../../lib/source/transform/transformer.h"

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
    float* dataset = create_dataset(1);
    dataset[0] = 90.0;
    dataset[1] = 45.0;
    dataset[2] = 200;
    
    configuration->dataset_size = 1;
    configuration->dataset = dataset;
    
    int* transformed_dataset = create_transformed_dataset(1);
    transformer->transform(configuration->bounds, configuration->tile_size, dataset, 1, transformed_dataset);
    
    CPPUNIT_ASSERT(transformed_dataset[0] == configuration->tile_size->width / 4 * 3);
    CPPUNIT_ASSERT(transformed_dataset[1] == configuration->tile_size->height / 4);
    CPPUNIT_ASSERT(transformed_dataset[2] == (int)dataset[2]);
    
    delete[] transformed_dataset;
    delete[] dataset; 
  }
  
  void multiPointDataset () {
    float* dataset = create_dataset(4);
    
    dataset[0] = 90.0;
    dataset[1] = 45.0;
    dataset[2] = 200;
    
    dataset[3] = -90.0;
    dataset[4] = 45.0;
    dataset[5] = 100;
    
    dataset[6] = 90.0;
    dataset[7] = -45.0;
    dataset[8] = 50;
    
    dataset[9] = -90.0;
    dataset[10] = -45.0;
    dataset[11] = 260;
    
    configuration->dataset_size = 4;
    configuration->dataset = dataset;
    
    int* transformed_dataset = create_transformed_dataset(4);
    transformer->transform(configuration->bounds, configuration->tile_size, dataset, 4, transformed_dataset);
    
    CPPUNIT_ASSERT(transformed_dataset[0] == configuration->tile_size->width / 4 * 3);
    CPPUNIT_ASSERT(transformed_dataset[1] == configuration->tile_size->height / 4);
    
    CPPUNIT_ASSERT(transformed_dataset[3] == configuration->tile_size->width / 4);
    CPPUNIT_ASSERT(transformed_dataset[4] == configuration->tile_size->height / 4);
    
    CPPUNIT_ASSERT(transformed_dataset[6] == configuration->tile_size->width / 4 * 3);
    CPPUNIT_ASSERT(transformed_dataset[7] == configuration->tile_size->height / 4 * 3);
    
    CPPUNIT_ASSERT(transformed_dataset[9] == configuration->tile_size->width / 4);
    CPPUNIT_ASSERT(transformed_dataset[10] == configuration->tile_size->height / 4 * 3);
    
    delete[] transformed_dataset;
    delete[] dataset; 
  }
  
  void emptyDataset () {
    float* dataset = create_dataset(0);
    
    configuration->dataset_size = 0;
    configuration->dataset = dataset;
    
    int* transformed_dataset = create_transformed_dataset(0);
    transformer->transform(configuration->bounds, configuration->tile_size, dataset, 0, transformed_dataset);
    
    delete[] transformed_dataset;
    delete[] dataset; 
  }

private:
  acid_maps::Configuration* configuration;
  acid_maps::Transformer* transformer;
  
  float* create_dataset(int points) {
    return new float[points * 3];
  }
  
  int* create_transformed_dataset(int points) {
    return new int[points * 3];
  }
  
};

CPPUNIT_TEST_SUITE_REGISTRATION( TransformerTest );
