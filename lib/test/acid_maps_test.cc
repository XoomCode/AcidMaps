#include <cppunit/extensions/HelperMacros.h>

class AcidMapsTest : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE( AcidMapsTest );
  CPPUNIT_TEST( testEmpty );
  CPPUNIT_TEST_SUITE_END();
public:
  void testEmpty () { int i = 5; CPPUNIT_ASSERT( i == 5 ); }
};
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( SampleTest, SampleTest );
