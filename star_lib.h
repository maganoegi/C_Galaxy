/*======================================
 * Galaxy Simulation using Quad-Trees
 * HEPIA 2018-2019 ITI 1
 * Sergey PLATONOV
 * star_lib.h
 * Library for star manipulations
======================================*/

#ifndef C_GALAXY_STAR_LIB_C
#define C_GALAXY_STAR_LIB_C

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "vec_lib.h"


#define G 0.0000000000667
#define Epsilon 30000.0

typedef struct __star {
    vec pos_t, pos_t_dt, acc;
    double mass;
} star;

star *new_star_vel(vec pos, vec vel, vec acc, double mass, double dt);  // new instance of a star
void reset_acceleration(star *s);                                       // acc to 0
void update_acceleration(star *s, const star *const s2);                // update acc with respect to another star
void update_position(star *s, double dt);                               // update star's position in function of time
void print_star(const star *const s);

void test_star_lib();

#endif //C_GALAXY_STAR_LIB_C