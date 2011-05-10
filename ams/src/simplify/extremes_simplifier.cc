/**
 * @file extremes_simplifier.cc
 * @brief Extremes simplifier implementation
 *
 * Find the maximum and minimum values
 *
 * @date 2011-01-27
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/point.h"
#include "./extremes_simplifier.h"
#include <cstring>
#include <climits>
#include <cmath>

namespace acid_maps {

void ExtremesSimplifier::simplify(Point* dataset, int dataset_size, Point* simplified_dataset, int& simplify_size) {
  int min_limit = INT_MIN;
  int max_limit = INT_MAX;
  
  int minimum = INT_MAX;
  int maximum = INT_MIN;
  
  // Used to store extremes indexes
  int min_index, max_index;
  int* indexes = new int[simplify_size];
  std::memset(indexes, -1, simplify_size * sizeof(indexes[0]));
  
  Point* point, *min, *max;
  for(int i = 0; i < simplify_size; i++){
  
    float min_limit = INT_MIN;
    float max_limit = INT_MAX;
  
    float minimum = INT_MAX;
    float maximum = INT_MIN;
  
    for(int j = 0; j < dataset_size; j++){
      if (in(j, indexes, simplify_size)) continue;

      point = dataset + j;
      if (point->value <= minimum && point->value >= min_limit){
        minimum = point->value;
        min_index = j;
        
      } else if(point->value >= maximum && point->value <= max_limit) {
        maximum = point->value;
        max_index = j;
      }
    }
    
    // Lower limit
    indexes[i] = min_index;
    min = dataset + min_index;
    min_limit = min->value;
    std::memcpy(simplified_dataset + i, min, sizeof(Point));
    
    // Exit if the array is full
    if(++i >= simplify_size) break;
    
    // Upper limit
    indexes[i] = max_index;
    max = dataset + max_index;
    max_limit = max->value;
    std::memcpy(simplified_dataset + i, max, sizeof(Point));
  }
  
  delete[] indexes;
  
}

bool ExtremesSimplifier::in(int index, int* array, int array_size){
  bool found = false;
  for(int i = 0; i < array_size; i++){
    if(array[i] == index){
      found = true;
      break;
    }
  }
  return found;
}

};  // namespace acid_maps

