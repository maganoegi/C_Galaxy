/*======================================
 * Galaxy Simulation using Quad-Trees
 * HEPIA 2018-2019 ITI 1
 * Sergey PLATONOV
 * main.c
 * Main
======================================*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "vec_lib.h"
#include "star_lib.h"
//#include "quadtree_lib.h"
#include "galaxy_lib.h"
#include "box_lib.h"

int main(int argc, char **argv) {
    test_vec_lib();
    test_box_lib();
    test_star_lib();
}