/*======================================
 * Galaxy Simulation using Quad-Trees
 * HEPIA 2018-2019 ITI 1
 * Sergey PLATONOV
 * box_lib.h
 * Library for box manipulations
======================================*/

#ifndef C_GALAXY_BOX_LIB_C
#define C_GALAXY_BOX_LIB_C

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "vec_lib.h"

typedef struct __box {
    double x0, x1, y0, y1;
} box;

box new_box(double x0, double x1, double y0, double y1);
box *divide_in_four(box b);
int is_inside(box b, vec v);
double compute_length(box b);
void print_box(box b);

void test_box_lib();

#endif //C_GALAXY_BOX_LIB_C