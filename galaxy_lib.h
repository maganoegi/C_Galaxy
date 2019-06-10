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

#define time_unit pow(10.0, 30.0)
#define R pow(10.0, 18.0)
#define m_solar (1.98892 * pow(10.0, 20.0))
#define m_min pow(10.0, 20.0)

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