#include <cppunit/extensions/HelperMacros.h>
#include "../../source/constants/constants.h"
#include "../../source/core/point.h"
#include "../../source/simplify/simplifier.h"
#include "../../source/simplify/copy_simplifier.h"

class CopySimplifierTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(CopySimplifierTest);
  CPPUNIT_TEST( singlePointDataset );
  CPPUNIT_TEST( multiPointDataset );
  CPPUNIT_TEST( emptyDataset );
  CPPUNIT_TEST_SUITE_END();
  
public:
  void setUp() {
    dataset = create_dataset();
    simplifier = new acid_maps::CopySimplifier();
  }
  
  void tearDown() {
    delete simplifier;
    delete[] dataset;
  }
  
  void singlePointDataset () {
    simplify_size = 1;
    acid_maps::Point* simplified_dataset = new acid_maps::Point[simplify_size];
    simplifier->simplify(dataset, dataset_size, simplified_dataset, simplify_size);

    CPPUNIT_ASSERT_EQUAL(dataset[0].x, simplified_dataset[0].x);
    CPPUNIT_ASSERT_EQUAL(dataset[0].y, simplified_dataset[0].y);
    CPPUNIT_ASSERT_EQUAL(dataset[0].value, simplified_dataset[0].value);
    
    delete[] simplified_dataset;
  }
  
  void multiPointDataset () {
    simplify_size = 2;
    acid_maps::Point* simplified_dataset = new acid_maps::Point[simplify_size];
    simplifier->simplify(dataset, dataset_size, simplified_dataset, simplify_size);

    CPPUNIT_ASSERT_EQUAL(dataset[0].x, simplified_dataset[0].x);
    CPPUNIT_ASSERT_EQUAL(dataset[0].y, simplified_dataset[0].y);
    CPPUNIT_ASSERT_EQUAL(dataset[0].value, simplified_dataset[0].value);

    CPPUNIT_ASSERT_EQUAL(dataset[1].x, simplified_dataset[1].x);
    CPPUNIT_ASSERT_EQUAL(dataset[1].y, simplified_dataset[1].y);
    CPPUNIT_ASSERT_EQUAL(dataset[1].value, simplified_dataset[1].value);
    
    delete[] simplified_dataset;
  }
  
  void emptyDataset () {
    simplify_size = 0;
    acid_maps::Point* simplified_dataset;
    simplifier->simplify(dataset, dataset_size, simplified_dataset, simplify_size);
  }

private:
  acid_maps::Simplifier* simplifier;
  acid_maps::Point* dataset;
  int dataset_size;
  int simplify_size;
  
  acid_maps::Point* create_dataset() {
    dataset_size = 4;
    
    acid_maps::Point* dataset = new acid_maps::Point[dataset_size];
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
    return dataset;
  }
  
};

CPPUNIT_TEST_SUITE_REGISTRATION( CopySimplifierTest );
