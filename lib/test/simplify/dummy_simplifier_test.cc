#include <cppunit/extensions/HelperMacros.h>
#include "../../source/constants/constants.h"
#include "../../source/simplify/simplifier.h"
#include "../../source/simplify/dummy_simplifier.h"

class DummySimplifierTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(DummySimplifierTest);
  CPPUNIT_TEST( singlePointDataset );
  CPPUNIT_TEST( multiPointDataset );
  CPPUNIT_TEST( emptyDataset );
  CPPUNIT_TEST_SUITE_END();
  
public:
  void setUp() {
    dataset_size = 4;
    dataset = create_dataset();
    simplifier = new acid_maps::DummySimplifier();
  }
  
  void tearDown() {
    delete simplifier;
    delete[] dataset;
  }
  
  void singlePointDataset () {
    float* simplified_dataset = new float[acid_maps::VPP];
    simplifier->simplify(dataset, dataset_size, 1, simplified_dataset);

    CPPUNIT_ASSERT_EQUAL(dataset[0], simplified_dataset[0]);
    CPPUNIT_ASSERT_EQUAL(dataset[1], simplified_dataset[1]);
    CPPUNIT_ASSERT_EQUAL(dataset[2], simplified_dataset[2]);
    
    delete[] simplified_dataset;
  }
  
  void multiPointDataset () {
    float* simplified_dataset = new float[2 * acid_maps::VPP];
    simplifier->simplify(dataset, dataset_size, 2, simplified_dataset);
    
    CPPUNIT_ASSERT_EQUAL(dataset[0], simplified_dataset[0]);
    CPPUNIT_ASSERT_EQUAL(dataset[1], simplified_dataset[1]);
    CPPUNIT_ASSERT_EQUAL(dataset[2], simplified_dataset[2]);
    
    CPPUNIT_ASSERT_EQUAL(dataset[3], simplified_dataset[3]);
    CPPUNIT_ASSERT_EQUAL(dataset[4], simplified_dataset[4]);
    CPPUNIT_ASSERT_EQUAL(dataset[5], simplified_dataset[5]);
    
    delete[] simplified_dataset;
  }
  
  void emptyDataset () {
    float* simplified_dataset;
    simplifier->simplify(dataset, dataset_size, 0, simplified_dataset);
  }

private:
  acid_maps::Simplifier* simplifier;
  float* dataset;
  int dataset_size;
  
  float* create_dataset() {
    float* dataset = new float[dataset_size * acid_maps::VPP];
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
    return dataset;
  }
  
};

CPPUNIT_TEST_SUITE_REGISTRATION( DummySimplifierTest );
