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
#include <cmath>
#include <cstdio>

namespace acid_maps {

static const float MARGIN = 1.01;

/**
 * TODO: SIMD
 */
void GridSimplifier::simplify(Point* dataset, int dataset_size, Point* simplified_dataset, int& simplify_size) {
  printf("\n# Grid simplifier\n\n");
  
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
  
  printf("# Bounding box\n");
  printf("min_x: %f\nmin_y: %f\nmax_x: %f\nmax_y: %f\n\n", min_x, min_y, max_x, max_y);
  
  // Step 2: Create the NxN simplified grid
  // In order to create a NxN proportional grid that will allow us to simplify the dataset
  // we need to calculate the closest perfect square number to get N
  int cells = std::floor(std::sqrt(simplify_size));
  float cell_width = (max_x - min_x) * MARGIN / cells;
  float cell_height = (max_y - min_y) * MARGIN / cells;
  
  printf("# Cells\n");
  printf("cells: %d\ncell_width: %f\ncell_height %f\n\n", cells, cell_width, cell_height);

  // Create the grid
  int grid_size = std::pow(cells, 2);
  Point* grid = new Point[grid_size];
  std::memset(grid, 0, grid_size * sizeof(grid[0]));
  
  // Create the grid counter
  int* cell_count = new int[grid_size];
  std::memset(cell_count, 0, grid_size * sizeof(cell_count[0]));
  printf("# Cell_count initialized\n");
  
  // Step 3: We iterate through the grid acummulating values
  // TODO: SIMD
  int index;
  for (int i = 0; i < dataset_size; i++){
    point = dataset + i;
    index =  (point->y - min_y) / cell_height * cells + (point->x - min_x) / cell_width;
    grid[index].x += point->x;
    grid[index].y += point->y;
    grid[index].value += point->value;
    cell_count[index]++;
  }
  printf("# Values accumulated\n");
  
  // Step 4: We calculate the average value for each cell
  // Also we check how many non empty cells exist
  simplify_size = 0;
  for (int i = 0; i < grid_size; i++){
    if(cell_count[i] > 0){
      grid[i].x /= cell_count[i];
      grid[i].y /= cell_count[i];
      grid[i].value /= cell_count[i];
      simplify_size++;
    }
  }
  printf("# Averaged\n");
  printf("# Grid %d => Simplify %d\n", grid_size, simplify_size);
  
  // Step 5: Copy valued points only <= simplify_size
  index = 0;
  for (int i = 0; i < grid_size; i++){
    if(cell_count[i] > 0) simplified_dataset[index++] = grid[i];
  }
  
}

};  // namespace acid_maps

