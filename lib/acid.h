#ifndef __ACID_H__
#define __ACID_H__

/**
 * A simple value with desired alpha
 */
typedef struct val {
	int value;
	int alpha;
} val;

/**
 * Coords are points with a value they 
 *
 */
typedef struct coord {
  int x;
  int y;
  int accum; // in case the coord represent a cell, it's the accumulated value of all the points in that cell
  int avg; // in case the coord represent a cell, it's the average value of all the points in that cell
  int max; // in case the coord represent a cell, it's the maximum value of all the points in that cell
  int most_freq; // in case the coord represent a cell, it's the value with most presence in that cell
  float dist; // to measure distance to some point and be able to qsort it
} coord;

/**
 * This structure represents an Acid Maps interval.
 * Its composed of a limit value (up_to), and 3 separated color components.
 * Each pixel, after receiving a value will be matched against an array of
 * intervals and get its corresponding color.
 */
typedef struct interv {
  int up_to;
  unsigned char r;
  unsigned char g;
  unsigned char b;
} interv;

/**
 * A bounding box
 */
typedef struct box {
	int top;
	int left;
	int bottom;
	int right;
} box;

/**
 * Configuration sent to Acid Maps server in the first POST request
 * It contains a set of points, the size of the array and its bounding box.
 */
typedef struct config {
	coord *coords;
	int size;
	box bbox;
} config;

/**
 * Renders a voronoi diagram in the given output buffer
 *
 * Params:
 * conf: configuration sent in the POST request
 * out: output buffer
 * intervs: intervals used to set isoline colors
 * intervs_size: intervals array length
 * diameter: (DEPRECATED) diameter used to cut the interpolation
 * alpha: image desired alpha
 */
void nearest_neigh(config conf, uint32_t *out, interv *intervs, int interv_size, int diameter, int alpha); 

/**
 * Renders an isoline in the given output buffer
 *
 * Params:
 * conf: configuration sent in the POST request
 * out: output buffer
 * intervs: intervals used to set isoline colors
 * intervs_size: intervals array length
 * diameter: (DEPRECATED) diameter used to cut the interpolation
 * alpha: image desired alpha
 */
void inverse_distance(config conf, uint32_t *out, interv *intervs, int interv_size, int diameter, int alpha); 

/**
 * Renders a heatmap image in the given output buffer 
 * 
 * Params:
 * conf: configuration sent in the POST request
 * out: output buffer
 * diameter: heatmap peaks diameter on y = 0
 * max_value: maximum value that any acummulated point can have
 */
void heatmap(config conf, uint32_t *out, int diameter, int max_value);

#endif
