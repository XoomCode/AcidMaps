#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h> 
#include <sys/time.h>
#include <stdint.h> 
#include <limits.h>

#include "acid.h"
#include "gradients.h"

// #define DEBUG 1
#define MAX(a, b) (a > b ? a : b) 
#define MIN(a, b) (a < b ? a : b)
#define MAX_ALPHA 255
#define LIMIT_VALUE 255
#define INV_DIST_STEP 8
#define RECURSIVE_STEPS 2
//#define CELL_SIZE 32 

/** 
 * Colorize the result and store it in a ABGR PNM
 * Used in heatmaps
 * 
 * Params:
 * out: Buffer where the PNM will be written to
 * vals: The array of calculated values
 * width: Image width
 * height: Image height
 * max_value: Used to determine the max value that any point can have
 */               
static void save_in_memory_as_gradient(uint32_t* out, int* vals, int width, int height, int max_value, int alpha) {

  // Allocate space needed
  memset(out, 0, width * height * sizeof(uint32_t));

  // Iterate through the whole image
  int x, y;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {

      // The normalized value its between 0 and max_value
      int v = *(vals + x*width + y);
      
      int normalized_value = v * (LIMIT_VALUE/(float)max_value);
      if (normalized_value > LIMIT_VALUE) {
        normalized_value = LIMIT_VALUE;
      }
      unsigned char c = (unsigned char)normalized_value;

      int a = (rainbow_colors[c] >> 24) & 0x000000ff;
      if (a > alpha) a = alpha;

      int r = (rainbow_colors[c] >> 16) & 0x000000ff;
      int g = (rainbow_colors[c] >> 8) & 0x000000ff;
      int b = (rainbow_colors[c]) & 0x000000ff;

      *(out + (height - y - 1)*height + x) = (a << 24) | (b << 16) | (g << 8) | r;
    }
  } 
}

/** 
 * Colorize the result and store it in a ABGR PNM
 * Used in isolines
 * 
 * Params:
 * out: Buffer where the PNM will be written to
 * vals: The array of calculated values
 * width: Image width
 * height: Image height
 * alphaV: Image desired alpha
 */
static void save_in_memory(uint32_t* out, int* vals, int width, int height, int alphaV) {
  int x, y;
  memset(out, 0, width * height * sizeof(uint32_t));
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) { 
      int color = *(vals + x*width + y);

      int a = color == 0 ? 0 : alphaV;
      int r = (color >> 16) & 0x000000ff;
      int g = (color >> 8) & 0x000000ff;
      int b = (color) & 0x000000ff;

      *(out + (height - y - 1)*height + x) = (a << 24) | (b << 16) | (g << 8) | r;
    }
  } 
}

/**
 * Calculate the IDW for the given point based on the given coordinates
 * Returns the calculated value.
 *
 * Params:
 * coords: Set of calculate points
 * size: Coords array size
 * c: Coord thats being interpolated
 * diameter: (DEPRECATED) diameter used to cut the interpolation
 */
static float calculate_idw(coord coords[], int size, coord c, int diameter) {
  int n;
  float accum_v = 0.0f;
  float accum_w = 0.0f;

  for (n = 0; n < size; n++) {
    coord *cn = (coords + n);
    float dx = c.x - cn->x;
    float dy = c.y - cn->y;
    float dt = sqrt(dx*dx + dy*dy);

    float w;
    if (dx == 0 && dy == 0){
      w = 1.0;
    } else {
      w = 1.0 / pow(dt, 2);
    }

    accum_v += w * cn->avg;
    accum_w += w;
  }

  return accum_v / accum_w;
}

/**
 * Calculate the IDW for the given point based on the given coordinates
 * Returns the calculated value.
 *
 * Params:
 * coords: Set of calculate points
 * size: Coords array size
 * c: Coord thats being interpolated
 * diameter: (DEPRECATED) diameter used to cut the interpolation
 */
static float calculate_voronoi(coord coords[], int size, coord c, int diameter) {
  int n;

  float min_dist = INT_MAX;
  int min_index = 0;
  for (n = 0; n < size; n++) {
    coord *cn = (coords + n);
    float dx = c.x - cn->x;
    float dy = c.y - cn->y;
    float dt = sqrt(dx*dx + dy*dy);

    if (dt < min_dist) {
      min_dist = dt;
      min_index = n;      
    }        
  }
  return (coords + min_index)->most_freq;
}

/**
 * Iterate through existing intervals to get the one that matches
 * Returns the color of the matching interval.
 *
 * Params:
 * intervs: Configured intervals
 * interv_size: Intervals array length
 * value: Value that will be matched with the intervals
 */
static int calc_rgb(interv intervs[], int interv_size, int value) {
  int i;
  for (i = 0; i < interv_size; i++) {
    if (value <= intervs[i].up_to) { 
      return (intervs[i].r << 16) | (intervs[i].g << 8) | (intervs[i].b);
    }
  }
  return (intervs[interv_size-1].r << 16) | (intervs[interv_size-1].g << 8) | (intervs[interv_size-1].b);
}

/**
 * Check if 4 values are the same
 */
static int same(int val1, int val2, int val3, int val4, int val5) {
  return (val1 == val2) && (val1 == val3) && (val1 == val4) && (val1 == val5);
}

/**
 * This function attemps to predict a region
 * Given an matrix, it checks if the corners have the same value. 
 * If that's the case, it fill the region with that value, assuming all the 
 * other coords have the same value.
 *
 * Adds a little error to the generated image, but improves performance a lot.
 *
 * Returns if the region could be predicted.
 *
 * Params:
 * mutable_coords: array of colors with values
 * size: coords array length
 * vals: buffer where the calculated values are stored
 * x: region first pixel horizontally
 * y: region first pixel vertically
 * width: region width
 * height: region height
 * interv: intervals array
 * interv_size: intervals array length
 * step: current recursive iteration
 * diameter: (DEPRECATED) diameter used to cut the interpolation
 * function: the function used to interpolate each point
 */
static int predict_region(coord mutable_coords[], int size, int* vals, int x, int y, int width, int height, interv intervs[], int interv_size, int step, int diameter, 
    float (*calc_inv_dist)(coord coords[], int size, coord c, int diameter)) {
  int sx, sy;

  int* top_left = vals + x*width + y;
  int* top_right = vals + x*width + y + step;
  int* bottom_right = vals + (x + step)*width + y + step;
  int* bottom_left = vals + (x + step)*width + y;
  int* center = vals + (x + step/2)*width + y + step/2;

  coord ref_c;
  ref_c.x = x;

  if (*top_left == 0) {
    ref_c.y = y;
    *top_left = calc_rgb(intervs, interv_size, calc_inv_dist(mutable_coords, size, ref_c, diameter));
  }

  if (y + step < height && x + step < width) { // if it's not the last step
    if (*top_right == 0) {
      ref_c.y = y + step;
      *top_right = calc_rgb(intervs, interv_size, calc_inv_dist(mutable_coords, size, ref_c, diameter));
    }

    if (*bottom_right == 0) {
      ref_c.y = y + step;
      ref_c.x = x + step;
      *bottom_right = calc_rgb(intervs, interv_size, calc_inv_dist(mutable_coords, size, ref_c, diameter));
    }

    if (*bottom_left == 0) {
      ref_c.y = y;
      ref_c.x = x + step;
      *bottom_left = calc_rgb(intervs, interv_size, calc_inv_dist(mutable_coords, size, ref_c, diameter));
    }

    if (*center == 0) {
      ref_c.y = y + step/2;
      ref_c.x = x + step/2;
      *center = calc_rgb(intervs, interv_size, calc_inv_dist(mutable_coords, size, ref_c, diameter));
    }
  }

  // If the value its the same in the corners
  // the full region its filled with that value
  if (y + step < height && x + step < width && same(*top_left, *top_right, *bottom_right, *bottom_left, *center)) {
    for (sx = 0; sx < step; sx++) {
      for (sy = 0; sy < step; sy++) {
        *(top_left + sx*width + sy) = *top_left;
      }
    }
    return 1;
  } else { 
    
    // calc value for each pixel
    return 0;       
  } 
}

/**
 * Using an interpolation function, calculate the values of a complete region
 * It iterates through each row and column, calculating the matching color
 * and storint it in the vals array.
 *
 * Params:
 * mutable_coords: array of colors with values
 * size: coords array length
 * vals: buffer where the calculated values are stored
 * x: region first pixel horizontally
 * y: region first pixel vertically
 * width: region width
 * height: region height
 * interv: intervals array
 * interv_size: intervals array length
 * step: current recursive iteration
 * diameter: (DEPRECATED) diameter used to cut the interpolation
 * function: the function used to interpolate each point
 */
static void calc_region(coord mutable_coords[], int size, int* vals, int x, int y, int width, int height, interv intervs[], int interv_size, int step, int diameter,
    float (*calc_inv_dist)(coord coords[], int size, coord c, int diameter)) {
  int sx, sy; 
  int* val_addr = (vals + x*width + y);

  coord ref_c;  
  for (sx = 0; sx < step; sx++) {
    for (sy = 0; sy < step; sy++) {
      ref_c.y = y + sy;
      ref_c.x = x + sx;

      *(val_addr + sx*width + sy) = calc_rgb(intervs, interv_size, calc_inv_dist(mutable_coords, size, ref_c, diameter));
    }
  }

}

/**
 * Recursively attemps to predict a region
 * If it fails, it calculates each value.
 *
 * Params:
 * mutable_coords: array of colors with values
 * size: coords array length
 * vals: buffer where the calculated values are stored
 * x: region first pixel horizontally
 * y: region first pixel vertically
 * width: region width
 * height: region height
 * interv: intervals array
 * interv_size: intervals array length
 * step: current recursive iteration
 * diameter: (DEPRECATED) diameter used to cut the interpolation
 * function: the function used to interpolate each point
 */
static void do_region(coord mutable_coords[], int size, int *vals, int x, int y, int width, int height, interv intervs[], int interv_size, int step, int level, int diameter,
    float (*calc_inv_dist)(coord coords[], int size, coord c, int diameter)) {
  if (!predict_region(mutable_coords, size, vals, x, y, width, height, intervs, interv_size, step, diameter, calc_inv_dist)) {
    if (level > 0) {
      int new_step = step/2;
      do_region(mutable_coords, size, vals, x, y, width, height, intervs, interv_size, new_step, level-1, diameter, calc_inv_dist);
      do_region(mutable_coords, size, vals, x, y + new_step, width, height, intervs, interv_size, new_step, level-1, diameter, calc_inv_dist);
      do_region(mutable_coords, size, vals, x + new_step, y + new_step, width, height, intervs, interv_size, new_step, level-1, diameter, calc_inv_dist);
      do_region(mutable_coords, size, vals, x + new_step, y, width, height, intervs, interv_size, new_step, level-1, diameter, calc_inv_dist);
    } else {
      calc_region(mutable_coords, size, vals, x, y, width, height, intervs, interv_size, step, diameter, calc_inv_dist);
    }
  }

}

/**
 * Calculates IDW for each point in the region
 * 
 * Params:
 * coords: Set of coords with data asociated.
 * size: coords length
 * width: tile width
 * height: tile height
 * interv: array of intervals that will be used to colorize the isoline
 * interv_size: interv array length
 * n_neigh: (DEPRECATED) number of neigbourghs used to calculate
 * diameter: (DEPRECATED) diameter used to cut the interpolation img
 * function: funciton used to calculate each pixel value
 */
static int* _do_inverse_distance(coord coords[], int size, int width, int height, interv intervs[], int interv_size, int n_neigh, int diameter,
    float (*calculate)(coord coords[], int size, coord c, int diameter)) {
  int i, x, y;                                    
  int step = INV_DIST_STEP;
  int *vals = malloc(sizeof(float) * width * height);
  memset(vals, 0, sizeof(float) * width * height);

  coord mutable_coords[size];
  for (i = 0; i < size; i++) {
    mutable_coords[i] = coords[i];
  }

  for (x = 0; x <= width - step; x += step) {
    for (y = 0; y <= height - step; y += step) {
      do_region(mutable_coords, size, vals, x, y, width, height, intervs, interv_size, step, RECURSIVE_STEPS, diameter, calculate);
    }
  }

  return vals;
} 

/**
 * This function is the one that calculates how much each point adds to
 * the current heatmap chart.
 * A cuadratic function is used to calculate
 * 
 * Params:
 * dx: distance in the x axis
 * dy: distance in the y axis
 * diameter: diameter of each heatmap peak in y = 0
 */
static float calc_heatmap_value(int dx, int dy, int diameter) {
  float dn = sqrt(pow(dx, 2) + pow(dy, 2));
  float d = (float)diameter;

  if (dn <= d) {
    return 100 * (d - dn) / d; // 100 is a reference value, could be another one                            
  } 
  return 0.0f;
}

/**
 * This function is the real implementation of that calculates the heatmap
 * It iterates through each coord in cooords, creating a buffer around it, 
 * and calculating the corresponding value.
 * 
 * Params:
 * coords: set of coords with data
 * size: coords length
 * width: tile width
 * height: tile height
 * diameter: diameter used to cut the interpolation img
 */
static int* _do_heatmap(coord coords[], int size, int width, int height, int diameter) {
  int i, x, y;
  int* vals = malloc(sizeof(int) * width * height);
  memset(vals, 0, sizeof(int) * width * height);
  
  int dx, dy = 0;
	float accum_v = 0.0;
  
  for (x = 0; x < width; x++) {
    for (y = 0; y < height; y++) {
    
    	accum_v = 0.0;
    	for (i = 0; i < size; i++) {
    		dx = coords[i].x - x;
    		dy = coords[i].y - y;
    		
				if (sqrt(pow(dx, 2) + pow(dy, 2)) > diameter) continue;
    		accum_v += calc_heatmap_value(dx, dy, diameter);
    	}
    	
			*(vals + x*width + y) = accum_v;
    }
  }
  
  return vals;
}

/**
 * Move each coord a given offset.
 * Its used to align points before interplation
 *
 * Params:
 * coords: set of coords with data
 * size: coords array length
 * offset_x: horizontally, how much each coord should be displaced
 * offset_y: vertically, how much each coord should be displaced
 */
static void offset_data(coord coords[], int size, int offset_x, int offset_y) {
  int i;
  for (i = 0; i < size; i++) {
    coords[i].x -= offset_x;
    coords[i].y -= offset_y;
  }
}

/**
 * Renders a heamap in the output buffer using the given configuration
 * 
 * Params:
 * config: stored configuration sent in the first POST request to acid maps
 * out: output buffer
 * diameter: heatmap peaks diameter on y = 0
 * max_value: used to determine the max value that any point can have
 */
void heatmap(config conf, uint32_t* out, int diameter, int max_value, int alpha) {
  
  int width = conf.bbox.right - conf.bbox.left;
  int height = conf.bbox.bottom - conf.bbox.top;

  coord *mutable_coords = malloc(sizeof(coord) * conf.size);
  memcpy(mutable_coords, conf.coords, sizeof(coord) * conf.size);

  offset_data(mutable_coords, conf.size, conf.bbox.left, conf.bbox.top);

  int* vals = _do_heatmap(mutable_coords, conf.size, width, height, diameter);

  save_in_memory_as_gradient(out, vals, width, height, max_value, alpha);

  free(vals);
  free(mutable_coords);
}

/**
 * Renders an interpolated image in the output buffer using the given configuration
 *
 * Params:
 * config: stored configuration sent in the first POST request to acid server
 * out: output buffer
 * interv: intervals array
 * interv_size: intervals array length
 * diameter: diameter used to cut the interpolation
 * mutable_coords: array of colors with values
 * size: coords array length
 * vals: buffer where the calculated values are stored
 * x: region first pixel horizontally
 * y: region first pixel vertically
 * width: region width
 * height: region height
 * step: current recursive iteration
 * function: the function used to interpolate each point
 */
static void interpolate(config conf, uint32_t *out, interv *intervs, int interv_size, int diameter,
  float (*calculate)(coord coords[], int size, coord c, int diameter), int alpha) {
  int width = conf.bbox.right - conf.bbox.left;
  int height = conf.bbox.bottom - conf.bbox.top;

  coord* mutable_coords = malloc(sizeof(coord) * conf.size);
  memcpy(mutable_coords, conf.coords, sizeof(coord) * conf.size);

  memset(out, 0, width * height * sizeof(uint32_t));

  offset_data(mutable_coords, conf.size, conf.bbox.left, conf.bbox.top);    

  int* vals = _do_inverse_distance(mutable_coords, conf.size, width, height, intervs, interv_size, conf.size/2, diameter, calculate);

  save_in_memory(out, vals, width, height, alpha);

  free(vals);
  free(mutable_coords);
}

/**
 * This public function is the one called from python
 * It calls do_inverse_distance function,using voronoi as the 
 * calculation function
 *
 * It renders a voronoi diagram in the output buffer
 *
 * Params:
 * conf: configuration sent in the POST request
 * out: output buffer
 * intervs: intervals used to set isoline colors
 * intervs_size: intervals array length
 * diameter: (DEPRECATED) diameter used to cut the interpolation
 * alpha: image desired alpha
 */
void nearest_neigh(config conf, uint32_t *out, interv *intervs, int interv_size, int diameter, int alpha) {
  interpolate(conf, out, intervs, interv_size, diameter, calculate_voronoi, alpha);
}

/**
 * This public function is the one called from python
 * It calls do_inverse_distance function,using idw as the 
 * calculation function
 * 
 * It renders an isoline in the output buffer
 *
 * Params:
 * conf: configuration sent in the POST request
 * out: output buffer
 * intervs: intervals used to set isoline colors
 * intervs_size: intervals array length
 * diameter: (DEPRECATED) diameter used to cut the interpolation
 * alpha: image desired alpha
 */
void inverse_distance(config conf, uint32_t *out, interv *intervs, int interv_size, int diameter, int alpha) {
  interpolate(conf, out, intervs, interv_size, diameter, calculate_idw, alpha);
}   

