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


// Initialize seed for random random generation
//srand(time(0));

// Function that allows for random double generation in different minmax ranges:
double randFrom(double min, double max) {
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

galaxy *create_and_init_galaxy(int num_bodies, box b, double dt) {
    // Allocation memory for all stars in galaxy (0th is super star):
    star** stars = malloc(num_bodies * sizeof(star*));

    // Initialization super star:
    vec* zero_vec = new_vec(0.0, 0.0);
    stars[0] = new_star_vel(
            *zero_vec, // init pos
            *zero_vec, // init velocity
            *zero_vec, // init acceleration
            (m_solar * pow(10.0, 6.0)), // mass
            0.0 // init dt
            );

    for(int i = 1; i < num_bodies; i++) {
        // Randomize a position
        vec* r_i_prototype = new_vec(0.5 - randFrom(0.0, 1.0), 0.5 - randFrom(0.0, 1.0));
        double alpha = R * (log10(1.0 - randFrom(0.0, 1.0))) / 1.8;
        vec* r_i = mul_vec(alpha, r_i_prototype);
        free(r_i_prototype);

        // Find mass
        double m_i = m_min + (randFrom(0.0, 10.0) * m_solar);

        // Calculate initial speed
        double phi = atan2(r_i->y, r_i->x);
        vec* v_i_prototype = new_vec(-sin(phi), cos(phi));
        vec* v_i = mul_vec(sqrt((G * (m_i + stars[0]->mass)) / norm(r_i)), v_i_prototype);
        free(v_i_prototype);

        // Add the star to the list
        stars[i] = new_star_vel(*r_i, *v_i, *zero_vec, m_i, dt);

        // Calculate acceleration
        update_acceleration(stars[i], stars[0]);
    }

    galaxy* g = malloc(sizeof(galaxy));
    g->num_bodies = num_bodies;
    g->b = b;
    g->stars = stars;

    return g;
}

// m_i = m_min + m_i'     m_i' = random(10.0) * m_solar
// r_i = R * ( (log(1 - random(1.0)) / 1.8) ) (0.5 - random(1.0)x, 0.5 - random(1.0 y))
// R = pow(10,18)
// m_0 = pow(10, 6) * m_solar, position = (0, 0), speed = (0, 0)
// Other stars have initial speed of:
// v_i = sqrt( (G(m_i + m_0)) / ||r_i|| ) * (-sin(phi), cos(phi))
// phi = atan2(r_iy / r_ix)

void reset_accelerations(galaxy* g) {
    vec* zero_vec = new_vec(0.0, 0.0);
    for(int i = 0; i < g->num_bodies; i++) {
        if(g->stars[i] != NULL) {
            g->stars[i]->acc = *zero_vec;
        }
    }
    free(zero_vec);
}

void update_positions(galaxy *g, double dt) {
    for(int i = 0; i < g->num_bodies; i++) {
        update_position(g->stars[i], dt);
    }
}

void free_galaxy(galaxy *g) {
    for(int i = 0; i < g->num_bodies; i++) {
        free(g->stars[i]);
    }
    free(g->stars);
    free(g);
}

void resize_galaxy(galaxy *g) {
        // If a star pos vector is outside of the box-allowed boundaries, it needs to be:
        // destroyed, freed, moved.

        // Check whether a vector is out of the boundaries -> put the pointer the NULL
        int q_2_rem = 0;
        for(int i = 0; i < g->num_bodies; i++) {
            if(!is_inside(g->b, g->stars[i]->pos_t)) {
                q_2_rem++;
                free(g->stars[i]);
                g->stars[i] = NULL;
//                printf("\n%p\n", g->stars[i]);
            }
        }
        g->num_bodies = g->num_bodies - q_2_rem;
}

void test_galaxy_lib() {

}
