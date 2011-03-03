#include <cppunit/extensions/HelperMacros.h>
#include "../../source/render/gradient_renderer.h"
#include <cstdlib>
#include <ctime>

class GradientRendererIntervalsTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(GradientRendererIntervalsTest);
  CPPUNIT_TEST( firstInterval );
  CPPUNIT_TEST_SUITE_END();
  
public:
  void setUp() {
    std::srand((unsigned)std::time(0));
    
    renderer = new acid_maps::GradientRenderer();
    intervals_size = std::rand() % 10 + 5;
    intervals = new float[intervals_size];
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

private:
  acid_maps::Renderer* renderer;
  float* intervals;
  int intervals_size;
};

CPPUNIT_TEST_SUITE_REGISTRATION( GradientRendererIntervalsTest );
