#include <cppunit/extensions/HelperMacros.h>

class AcidMapsTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(AcidMapsTest);
  CPPUNIT_TEST( defaultConfiguration );
  CPPUNIT_TEST_SUITE_END();
  
public:
  void defaultConfiguration () {
    CPPUNIT_ASSERT(true);
  }
};

//CPPUNIT_TEST_SUITE_REGISTRATION( AcidMapsTest );
