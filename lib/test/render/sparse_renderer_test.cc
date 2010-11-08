#include <cppunit/extensions/HelperMacros.h>

class SparseRendererTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(SparseRendererTest);
  CPPUNIT_TEST( defaultConfiguration );
  CPPUNIT_TEST_SUITE_END();
  
public:
  void defaultConfiguration () {
    
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION( SparseRendererTest );
