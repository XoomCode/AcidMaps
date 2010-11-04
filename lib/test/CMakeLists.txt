cmake_minimum_required (VERSION 2.8) 
project (ACID_MAPS_LIB_TEST) 

FILE(GLOB_RECURSE test_sources *_test.cc)
ADD_EXECUTABLE(test_runner test_runner.cc ${test_sources})
TARGET_LINK_LIBRARIES(test_runner cppunit acid-maps)
FOREACH(test ${test_sources})
        GET_FILENAME_COMPONENT(test_name ${test} NAME_WE)
        ADD_TEST(${test_name} test_runner ${test_name})
ENDFOREACH(test)

