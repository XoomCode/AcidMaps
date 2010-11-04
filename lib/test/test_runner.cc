/** 
 * This program is responsible of running each test
 * Also if a test is specified only that will run
 *
 * @date 2010-11-04
 * @authors Fabio R. Panettieri
 */

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main (int argc, char* argv[]) {
  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();

  // run all tests if none specified on command line 
  CppUnit::Test* test = registry.makeTest();
  if (argc > 1){
    test = test->findTest(argv[1]);
  }

  runner.addTest(test);
  bool failed = runner.run("", false);
  return !failed;
}
