/*======================================
 * Galaxy Simulation using Quad-Trees
 * HEPIA 2018-2019 ITI 1
 * Sergey PLATONOV
 * star_lib.h
 * Library for galaxy manipulations
======================================*/

#ifndef C_GALAXY_GALAXY_LIB_C
#define C_GALAXY_GALAXY_LIB_C

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "vec_lib.h"
#include "star_lib.h"
#include "box_lib.h"

#define time_unit 1000000000000000.0
#define R 1000000000000000000.0
#define m_solar 198892000000000000000.0
#define m_min 100000000000000000000.0

typedef struct __galaxy {
    int num_bodies;
    star **stars;
    box b;
} galaxy;

galaxy *create_and_init_galaxy(int num_bodies, box b, double dt);
void reset_accelerations(galaxy *g);
void update_positions(galaxy *g, double dt);
void free_galaxy(galaxy *g);
void resize_galaxy(galaxy *g);

void test_galaxy_lib();

#endif //C_GALAXY_GALAXY_LIB_C