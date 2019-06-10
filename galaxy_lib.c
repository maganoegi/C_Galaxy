/*======================================
 * Galaxy Simulation using Quad-Trees
 * HEPIA 2018-2019 ITI 1
 * Sergey PLATONOV
 * star_lib.c
 * Library for galaxy manipulations
======================================*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "vec_lib.h"
#include "star_lib.h"
#include "galaxy_lib.h"
#include "box_lib.h"
#include <math.h>
#include <time.h>

#define time_unit pow(10, 30)

//float x = (float)rand()/(float)(RAND_MAX/a);

double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

galaxy *create_and_init_galaxy(int num_bodies, box b, double dt) {
    star** stars = malloc(num_bodies * sizeof(star*));
    for(int i = 0; i < num_bodies; i++) {
        stars[i] = new_star_vel();
    }

    galaxy* g = malloc(sizeof(galaxy));
    g->num_bodies = num_bodies;
    g->b = b;
    g->
}

// m_i = m_min + m_i'     m_i' = random(10.0) * m_solar
// r_i = R * ( (log(1 - random(1.0)) / 1.8) ) (0.5 - random(1.0)x, 0.5 - random(1.0 y))
// R = pow(10,18)
// m_0 = pow(10, 6) * m_solar, position = (0, 0), speed = (0, 0)
// Other stars have initial speed of:
// v_i = sqrt( (G(m_i + m_0)) / ||r_i|| ) * (-sin(phi), cos(phi))
// phi = atan2(r_iy / r_ix)

void reset_accelerations(galaxy *g) {

}

void update_positions(galaxy *g, double dt) {

}

void free_galaxy(galaxy *g) {

}

void resize_galaxy(galaxy *g) {

}

void test_galaxy_lib() {

}
