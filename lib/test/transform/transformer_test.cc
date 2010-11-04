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
    configuration->bounds = new acid_maps::Bounds(-180, -90, 180, 90);
    configuration->width = 512;
    configuration->height = 512;
    
    transformer = new acid_maps::Transformer();
  }
  
  void tearDown() {
    delete transformer;
    delete configuration;
  }
  
  void singlePointDataset () {
    float* dataset = create_dataset(1);
    dataset[0] = 90.0;
    dataset[1] = 45.0;
    dataset[2] = 200;
    
    configuration->dataset_size = 1;
    configuration->dataset = dataset;
    
    /// Transform dataset
    transformer->transform(configuration);
    
    CPPUNIT_ASSERT(dataset[0] == configuration->width / 4 * 3);
    CPPUNIT_ASSERT(dataset[1] == configuration->height / 4);
  }
  
  void multiPointDataset () {
    /// Create a single point dataset
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
    
    /// Transform dataset
    transformer->transform(configuration);
    
    CPPUNIT_ASSERT(dataset[0] == configuration->width / 4 * 3);
    CPPUNIT_ASSERT(dataset[1] == configuration->height / 4);
    
    CPPUNIT_ASSERT(dataset[3] == configuration->width / 4);
    CPPUNIT_ASSERT(dataset[4] == configuration->height / 4);
    
    CPPUNIT_ASSERT(dataset[6] == configuration->width / 4 * 3);
    CPPUNIT_ASSERT(dataset[7] == configuration->height / 4 * 3);
    
    CPPUNIT_ASSERT(dataset[9] == configuration->width / 4);
    CPPUNIT_ASSERT(dataset[10] == configuration->height / 4 * 3);
  }
  
  void emptyDataset () {
    float* dataset = create_dataset(0);
    
    configuration->dataset_size = 0;
    configuration->dataset = dataset;
    
    /// Transform dataset
    transformer->transform(configuration);
  }

private:
  acid_maps::Configuration* configuration;
  acid_maps::Transformer* transformer;
  
  float* create_dataset(int points) {
    return new float[points * 3];
  }
  
};

CPPUNIT_TEST_SUITE_REGISTRATION( TransformerTest );
