#include <cppunit/extensions/HelperMacros.h>
#include "../../../lib/source/core/configuration.h"
#include "../../../lib/source/core/bounds.h"
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
    transformer = new acid_maps::Transformer();
  }
  
  void tearDown() {
    delete transformer;
    delete configuration;
  }
  
  void singlePointDataset () {
    world_extent();
    tile_size();
    
    /// Create a single point dataset
    int dataset_size = 3;
    float* dataset = new float[dataset_size];
    dataset[0] = 45.0;
    dataset[1] = 45.0;
    dataset[2] = 200;
    
    configuration->dataset_size = dataset_size;
    configuration->dataset = dataset;
    
    /// Transform dataset
    transformer->transform(configuration);
    
/*  CPPUNIT_ASSERT(dataset[0] == configuration->width * 3/4);
    CPPUNIT_ASSERT(dataset[1] == configuration->height * 1/4);*/
  }
  
  void multiPointDataset () {
    
  }
  
  void emptyDataset () {
    
  }

private:
  acid_maps::Configuration* configuration;
  acid_maps::Transformer* transformer;
  
  void world_extent () {
    configuration->bounds = new acid_maps::Bounds(-180, -90, 180, 90);
  }
  
  void tile_size () {
    configuration->width = 512;
    configuration->height = 512;
  }
  
};

CPPUNIT_TEST_SUITE_REGISTRATION( TransformerTest );
