cmake_minimum_required (VERSION 2.8) 
project (ACID_MAPS_LIB) 

FILE(GLOB_RECURSE sources *.cc)
ADD_LIBRARY (acid-maps SHARED ${sources})

