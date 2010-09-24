#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h> 
#include <sys/time.h>
#include <stdint.h> 
#include <limits.h>

#include "acid.h"

// #define DEBUG 1
#define MAX(a, b) (a > b ? a : b) 
#define MIN(a, b) (a < b ? a : b)
#define MAX_ALPHA 255
#define LIMIT_VALUE 255
#define INV_DIST_STEP 8
#define RECURSIVE_STEPS 2
//#define CELL_SIZE 32 

/**
 * Heatmap color gradient
 */
static unsigned int gradient_colors[] = {0,167772415UL,335544575UL,503316726UL,671088889UL,855638261UL,1023410423UL,1191182584UL,1358954741UL,1526726902UL,1711276277UL,1879048438UL,2046820599UL,2214592757UL,2382364918UL,2566914293UL,2734686453UL,2902458614UL,3070230773UL,3238002934UL,3422552309UL,3590324469UL,3758096630UL,3925868788UL,4093640949UL,4278190326UL,4278191862UL,4278193398UL,4278195190UL,4278196726UL,4278198518UL,4278200054UL,4278201590UL,4278203382UL,4278204918UL,4278206710UL,4278208246UL,4278209782UL,4278211574UL,4278213110UL,4278214902UL,4278216438UL,4278217974UL,4278219766UL,4278221302UL,4278223094UL,4278224630UL,4278226166UL,4278227958UL,4278229494UL,4278296822UL,4278232053UL,4278232821UL,4278233588UL,4278234356UL,4278235124UL,4278235891UL,4278236659UL,4278237426UL,4278238194UL,4278238962UL,4278239729UL,4278240497UL,4278241264UL,4278242032UL,4278242800UL,4278243567UL,4278244335UL,4278245102UL,4278245870UL,4278246638UL,4278247405UL,4278248173UL,4278248940UL,4278249708UL,4278250732UL,4278250722UL,4278250969UL,4278251215UL,4278251462UL,4278251452UL,4278251699UL,4278251945UL,4278252192UL,4278252183UL,4278252429UL,4278252676UL,4278252922UL,4278252913UL,4278253159UL,4278253406UL,4278253652UL,4278253643UL,4278253890UL,4278254136UL,4278254383UL,4278254373UL,4278254620UL,4278254866UL,4278255113UL,4278255360UL,4278910720UL,4279566080UL,4280221440UL,4280876800UL,4281597696UL,4282253056UL,4282908416UL,4283563776UL,4284219136UL,4284940032UL,4285595392UL,4286250752UL,4286906112UL,4287561472UL,4288282368UL,4288937728UL,4289593088UL,4290248448UL,4290903808UL,4291624704UL,4292280064UL,4292935424UL,4293590784UL,4294246144UL,4294967040UL,4294900736UL,4294834432UL,4294768384UL,4294702080UL,4294636032UL,4294569728UL,4294503680UL,4294437376UL,4294371328UL,4294305024UL,4294238976UL,4294172672UL,4294106624UL,4294040320UL,4293974272UL,4293907968UL,4293841920UL,4293775616UL,4293709568UL,4293643264UL,4293577216UL,4293510912UL,4293444864UL,4293378560UL,4293378048UL,4293377536UL,4293442560UL,4293507584UL,4293572608UL,4293637632UL,4293702656UL,4293767680UL,4293832704UL,4293897728UL,4293962752UL,4294027776UL,4294092800UL,4294158080UL,4294223104UL,4294288128UL,4294353152UL,4294418176UL,4294483200UL,4294548224UL,4294613248UL,4294678272UL,4294743296UL,4294808320UL,4294873344UL,4294938624UL,4294937088UL,4294935552UL,4294934016UL,4294932480UL,4294931200UL,4294929664UL,4294928128UL,4294926592UL,4294925312UL,4294923776UL,4294922240UL,4294920704UL,4294919424UL,4294917888UL,4294916352UL,4294914816UL,4294913536UL,4294912000UL,4294910464UL,4294908928UL,4294907648UL,4294906112UL,4294904576UL,4294903040UL,4294901760UL,4294903045UL,4294904330UL,4294905615UL,4294906900UL,4294908185UL,4294909470UL,4294910755UL,4294912040UL,4294913325UL,4294914867UL,4294916152UL,4294917437UL,4294918722UL,4294920007UL,4294921292UL,4294922577UL,4294923862UL,4294925147UL,4294926432UL,4294927974UL,4294929259UL,4294930544UL,4294931829UL,4294933114UL,4294934399UL,4294935684UL,4294936969UL,4294938254UL,4294939539UL,4294941081UL,4294942366UL,4294943651UL,4294944936UL,4294946221UL,4294947506UL,4294948791UL,4294950076UL,4294951361UL,4294952646UL,4294954188UL,4294955473UL,4294956758UL,4294958043UL,4294959328UL,4294960613UL,4294961898UL,4294963183UL,4294964468UL,4294965753UL,4294967295UL,4294967295UL,4294967295UL,4294967295UL,4294967295UL,4294967295UL};

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
static void save_in_memory_as_gradient(uint32_t *out, val *vals, int width, int height, int max_value) {

  // Allocate space needed
  memset(out, 0, width * height * sizeof(uint32_t));

  // Iterate through the whole image
  int x, y;
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {

      // The normalized value its between 0 and max_value
      val *v = (vals + x*width + y);
      int normalized_value = v->value * (LIMIT_VALUE/(float)max_value);
      if (normalized_value > LIMIT_VALUE) {
        normalized_value = LIMIT_VALUE;
      }

      unsigned char c = (unsigned char)normalized_value;
      int alpha;
      if (c == 0){
        alpha = 0;
      } else {
        alpha = MIN(v->alpha, MAX_ALPHA);
      }

      int r = (gradient_colors[c] >> 16) & 0x000000ff;
      int g = (gradient_colors[c] >> 8) & 0x000000ff;
      int b = (gradient_colors[c]) & 0x000000ff;

      *(out + (height - y - 1)*height + x) = (alpha << 24) | (b << 16) | (g << 8) | r;
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
static void save_in_memory(uint32_t *out, int *vals, int width, int height, int alphaV) {
  int x, y;
  memset(out, 0, width * height * sizeof(uint32_t));
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) { 
      int color = *(vals + x*width + y);
      int alpha;
      if (color == 0) 
        alpha = 0;
      else
        alpha = alphaV;

      int r = (color >> 16) & 0x000000ff;
      int g = (color >> 8) & 0x000000ff;
      int b = (color) & 0x000000ff;

      *(out + (height - y - 1)*height + x) = (alpha << 24) | (b << 16) | (g << 8) | r;
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
static int predict_region(coord mutable_coords[], int size, int *vals, int x, int y, int width, int height, interv intervs[], int interv_size, int step, int diameter, 
    float (*calc_inv_dist)(coord coords[], int size, coord c, int diameter)) {
  int sx, sy;
  int *val_addr, *val_addr1, *val_addr2, *val_addr3, *val_addr4 = 0;

  val_addr = (vals + x*width + y);
  val_addr1 = (vals + x*width + y + step);
  val_addr2 = (vals + (x + step)*width + y + step);
  val_addr3 = (vals + (x + step)*width + y);
  val_addr4 = (vals + (x + step/2)*width + y + step/2);

  coord ref_c;
  ref_c.x = x;

  if (*val_addr == 0) {
    ref_c.y = y;
    *val_addr = calc_rgb(intervs, interv_size, calc_inv_dist(mutable_coords, size, ref_c, diameter));
  }

  if (y + step < height && x + step < width) { // if it's not the last step
    if (*val_addr1 == 0) {
      ref_c.y = y + step;
      *val_addr1 = calc_rgb(intervs, interv_size, calc_inv_dist(mutable_coords, size, ref_c, diameter));
    }

    if (*val_addr2 == 0) {
      ref_c.y = y + step;
      ref_c.x = x + step;
      *val_addr2 = calc_rgb(intervs, interv_size, calc_inv_dist(mutable_coords, size, ref_c, diameter));
    }

    if (*val_addr3 == 0) {
      ref_c.y = y;
      ref_c.x = x + step;
      *val_addr3 = calc_rgb(intervs, interv_size, calc_inv_dist(mutable_coords, size, ref_c, diameter));
    }

    if (*val_addr4 == 0) {
      ref_c.y = y + step/2;
      ref_c.x = x + step/2;
      *val_addr4 = calc_rgb(intervs, interv_size, calc_inv_dist(mutable_coords, size, ref_c, diameter));
    }
  }

  // If the value its the same in the corners
  // the full region its filled with that value
  if (y + step < height && x + step < width && same(*val_addr, *val_addr1, *val_addr2, *val_addr3, *val_addr4)) {
    for (sx = 0; sx < step; sx++) {
      for (sy = 0; sy < step; sy++) {
        *(val_addr + sx*width + sy) = *val_addr;
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
static void calc_region(coord mutable_coords[], int size, int *vals, int x, int y, int width, int height, interv intervs[], int interv_size, int step, int diameter,
    float (*calc_inv_dist)(coord coords[], int size, coord c, int diameter)) {
  int sx, sy; 
  int *val_addr;

  val_addr = (vals + x*width + y);

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
  float dn = sqrt(dx*dx + dy*dy);

  if (dn <= diameter) {
    float w = pow(((diameter - dn)/(float)diameter), 2);
    return w * 100; // 100 is a reference value, could be another one                            
  } else {
    return 0.0f;
  }
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
static val *_do_heatmap(coord coords[], int size, int width, int height, int diameter) {
  int i, j, x, y;
  val *vals = malloc(sizeof(val) * width * height);
  memset(vals, 0, sizeof(val) * width * height); 

  for (i = 0; i < size; i++) {
    coord c = coords[i];

    for (x = c.x-diameter/2; x < c.x+diameter/2; x++) {
      if (x < 0 || x > width-1)
        continue;

      for (y = c.y-diameter/2; y < c.y+diameter/2; y++) {
        if (y < 0 || y > height-1)
          continue;

        float dx = x - c.x;
        float dy = y - c.y;
        float d = dx*dx + dy*dy;
        float not_sqrt_radio = (diameter/2.0) * (diameter/2.0); 
        if (d >= not_sqrt_radio)
          continue;

        val *val_addr= vals + x*width + y;

        int cand_alpha = MAX_ALPHA * ((not_sqrt_radio - d)/not_sqrt_radio);
        val_addr->alpha += cand_alpha;

        if (val_addr->value != 0)
          continue;

        float accum_v = 0.0;

        for (j = 0; j < size; j++) {
          accum_v += calc_heatmap_value(x - coords[j].x, y - coords[j].y, diameter);
        }
        val_addr->value = accum_v;
      }                            
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
void heatmap(config conf, uint32_t* out, int diameter, int max_value) {
  int width = conf.bbox.right - conf.bbox.left;
  int height = conf.bbox.bottom - conf.bbox.top;

  coord *mutable_coords = malloc(sizeof(coord) * conf.size);
  memcpy(mutable_coords, conf.coords, sizeof(coord) * conf.size);

  offset_data(mutable_coords, conf.size, conf.bbox.left, conf.bbox.top);

  val *vals = _do_heatmap(mutable_coords, conf.size, width, height, diameter);

  save_in_memory_as_gradient(out, vals, width, height, max_value);

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

