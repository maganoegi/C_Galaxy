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

void free_galaxy(galaxy *g) { // NEED TO FREE THE VECTORS!!!
    for(int i = 0; i < g->num_bodies; i++) {
        vec_free(&g->stars[i]->pos_t);
        vec_free(&g->stars[i]->pos_t_dt);
        vec_free(&g->stars[i]->acc);
        free(g->stars[i]);
    }
    free(g->stars);
    free(g);
}

void resize_galaxy(galaxy *g) {
        /*===========================================================================================
            * If a star position vector is outside of the box-allowed boundaries, it needs to be:
                * tested
                * valid values copied to tmp, invalid copies counted
                * reallocated with the new "valid" dimension
                * values moved back
                * tmp destroyed
        ===========================================================================================*/
        int q_2_rem = 0;
        star** tmp = malloc(g->num_bodies * sizeof(star*));
        for(int i = 0; i < g->num_bodies; i++) {
            if(!is_inside(g->b, g->stars[i]->pos_t)) {
                q_2_rem++;
            } else {
                tmp[i] = g->stars[i];
            }
        }

        g->num_bodies = g->num_bodies - q_2_rem;
        g->stars = realloc(g->stars, g->num_bodies * sizeof(star*));

        if(g->num_bodies == 1) {
            EXIT_SUCCESS;
        }

        for(int i = 0; i < g->num_bodies; i++) {
            if(is_inside(g->b, g->stars[i]->pos_t)) {
                g->stars[i] = tmp[i];
                //print_star(g->stars[i]); 
            }     
        }

        free(tmp);
}

void test_galaxy_lib() {
    // Initialize seed for random random generation (seeder needs to be just outside the function)

    galaxy* g = create_and_init_galaxy(5, new_box(-1.0, 2.0, -2.0, 1.0), 1.0);

//    for(int i = 0; i < g->num_bodies; i++) {
//        update_positions(g, 2.0 * time_unit);
//        print_star(g->stars[i]);
//    }
    for(int i = 1; i < 10; i++) {
        update_acceleration(g->stars[1], g->stars[0]);
        update_positions(g, (double)i * time_unit);
        print_star(g->stars[1]);
    }
}
