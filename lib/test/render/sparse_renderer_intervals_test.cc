#include <cppunit/extensions/HelperMacros.h>
#include "../../source/render/sparse_renderer.h"
#include <cstdlib>
#include <ctime>

class SparseRendererIntervalsTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(SparseRendererIntervalsTest);
  CPPUNIT_TEST( firstInterval );
  CPPUNIT_TEST( evenInterval );
  CPPUNIT_TEST( oddInterval );
  CPPUNIT_TEST( firstValueInterval );
  CPPUNIT_TEST( lastValueInterval );
  CPPUNIT_TEST( firstValue );
  CPPUNIT_TEST( lastValue );
  CPPUNIT_TEST( randomIntervals );
  CPPUNIT_TEST( outOfBoundsFirstInterval );
  CPPUNIT_TEST( outOfBoundsLastInterval );
  CPPUNIT_TEST_SUITE_END();
  
public:
  void setUp() {
    std::srand((unsigned)std::time(0));
    
    renderer = new acid_maps::SparseRenderer();
    intervals_size = std::rand() % 10 + 5;
    intervals = new int[intervals_size];
    for (int i = 0; i < intervals_size; i++) {
      intervals[i] = (i + 1) * 10;
    }
  }
  
  void tearDown() {
    delete renderer;
    delete[] intervals;
  }
  
  void firstInterval () {
    CPPUNIT_ASSERT_EQUAL(0, renderer->interval(9, intervals, intervals_size));
  }
  
  void evenInterval () {
    CPPUNIT_ASSERT_EQUAL(2, renderer->interval(24, intervals, intervals_size));
  }
  
  void oddInterval () {
    CPPUNIT_ASSERT_EQUAL(3, renderer->interval(35, intervals, intervals_size));
  }
  
  void firstValueInterval () {
    CPPUNIT_ASSERT_EQUAL(3, renderer->interval(31, intervals, intervals_size));
  }
  
  void lastValueInterval () {
    CPPUNIT_ASSERT_EQUAL(4, renderer->interval(50, intervals, intervals_size));
  }
  
  void firstValue () {
    CPPUNIT_ASSERT_EQUAL(0, renderer->interval(0, intervals, intervals_size));
  }
  
  void lastValue () {
    CPPUNIT_ASSERT_EQUAL(intervals_size - 1, renderer->interval(intervals_size * 10, intervals, intervals_size));
  }
  
  void randomIntervals () {
    int value, interval;
    int validations = std::rand() % 80 + 20;
    for (int i = 0; i < validations; i++) {
      value = std::rand() % (intervals_size * 10) - 20;
      interval = value <= 0 ? 0 : (value - 1) / 10;
      CPPUNIT_ASSERT_EQUAL(interval, renderer->interval(value, intervals, intervals_size));
    }
  }
  
  void outOfBoundsFirstInterval () {
    CPPUNIT_ASSERT_EQUAL(0, renderer->interval(-4, intervals, intervals_size));
  }
  
  void outOfBoundsLastInterval () {
    CPPUNIT_ASSERT_EQUAL(intervals_size - 1, renderer->interval(intervals_size * 11 , intervals, intervals_size));
  }

private:
  acid_maps::Renderer* renderer;
  int* intervals;
  int intervals_size;
};

CPPUNIT_TEST_SUITE_REGISTRATION( SparseRendererIntervalsTest );
