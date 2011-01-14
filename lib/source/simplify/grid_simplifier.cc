/**
 * @file grid_simplifier.cc
 * @brief Grid simplifier implementation
 *
 * @date 2011-01-12
 * @authors Fabio R. Panettieri
 */

#include "../constants/constants.h"
#include "../core/point.h"
#include "./grid_simplifier.h"
#include <climits>
#include <cstring>

#include <cstdio>

#include <cmath>

namespace acid_maps {

void GridSimplifier::simplify(Point* dataset, int dataset_size, int simplify_size, Point* simplified_dataset) {
  int size = simplify_size <= dataset_size ? simplify_size : dataset_size;
  
  // Step 1: Get the bounding box
  float min_x = INT_MAX;
  float min_y = INT_MAX;
  float max_x = INT_MIN;
  float max_y = INT_MIN;
  
  Point* point;
  for (int i = 0; i < dataset_size; i++){
    point = dataset + i;
    if(point->x < min_x) min_x = point->x;
    if(point->x > max_x) max_x = point->x;
    if(point->y < min_y) min_y = point->y;
    if(point->y > max_y) max_y = point->y;
  }
  
  // Step 2: Create the NxN simplified grid
  // In order to create a NxN proportional grid that will allow us to simplify the dataset
  // we need to calculate the closest perfect square number to get N
  int cells = std::floor(std::sqrt(size));
  float cell_width = (max_x - min_x) / cells;
  float cell_height = (max_y - min_y) / cells;
  
  printf("Cells %d %f %f\n", cells, cell_width, cell_height);

  int grid_size = std::pow(cells, 2);
  int* cell_count = new int[grid_size];
  std::memset(cell_count, 0, grid_size * sizeof(cell_count[0]));
  
  printf("cell_count initialized\n");
  std::memset(simplified_dataset, 0, simplify_size * sizeof(simplified_dataset[0]));

  // Step 3: We iterate through the grid acummulating values
  // TODO: Determine what we do when the simplified size is not a perfect square
  int index;
  for (int i = 0; i < dataset_size; i++){
    point = dataset + i;
    index  = (point->y - min_y) / cell_height * cells + (point->x - min_x) / cell_width;
    if(index >= dataset_size) printf("HASTA LA PIJA: %d\n", index);
    simplified_dataset[index].x += point->x;
    simplified_dataset[index].y += point->y;
    simplified_dataset[index].value += point->value;
    cell_count[index]++;
  }
  
  // Step 4: We calculate the average value for each cell
  // TODO: check the possibility of using acummulated value instead of the average
//  for (int i = 0; i < size; i++){
//    if(cell_count[i] > 0){
//      simplified_dataset[i].x /= cell_count[i];
//      simplified_dataset[i].y /= cell_count[i];
//      simplified_dataset[i].value /= cell_count[i];
//    }
//  }
//  
//  /// DEBUG
//  for (int y = 0; y < cells; y++){
//    for (int x = 0; x < cells; x++){
//      point = dataset + y * cells + x;
//      //if(cell_count[y * cells + x] > 0) std::printf("%f,%f %d\n", point->x, point->y, point->value);
//    }
//  }
}

};  // namespace acid_maps

