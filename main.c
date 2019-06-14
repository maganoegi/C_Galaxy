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
#include <time.h>
//#include <SDL2/SDL.h>

#include "vec_lib.h"
#include "star_lib.h"
#include "quadtree_lib.h"
#include "galaxy_lib.h"
#include "box_lib.h"

int input_error_handler(int argc, char **argv) {
    if(argc != 3) {
        fprintf(stderr, "%s========== Invalid Parameters Error ===========\n%s"
                        "%s  Please provide exactly 2 arguments (int, double)%s\n"
                        "%s  └> Number of stars, and Theta %s\n"
                        "%s===============================================%s\n\n", KRED, KNRM, KMAG, KNRM,
                KCYN, KNRM, KRED, KNRM);
        return EXIT_FAILURE;
    }
    return 0;
}

void galaxy_display(galaxy* g) {

}

int main(int argc, char **argv) {
    input_error_handler(argc, argv);
    /*======================================
        * Initialization
    ======================================*/
    int num_stars = atoi(argv[1]);
    double theta = atof(argv[2]);
    int iter = 1000; // number of temporal iterations
    srand(time(NULL)); // seed for rng
    box domain = new_box(
            -100000000000000000000000.0, // x0
            100000000000000000000000.0,  // x1
            -100000000000000000000000.0, // y0
            100000000000000000000000.0   // y1
            );

    /*======================================
        * Galaxy Simulation
    ======================================*/
    galaxy* g = create_and_init_galaxy(num_stars, domain, 0.0);
    for(int i = 0; i < iter; i++) {
        double dt = (double)i * time_unit;

        resize_galaxy(g);
        galaxy_display(g);
        reset_accelerations(g);
        quad_tree* qt = create_quad_tree_from_galaxy(g);
        update_accelerations_of_all_stars(qt->root, g, theta);
        update_positions(g, dt);
        free_quad_tree(qt);
    }

    free_galaxy(g);

    /*======================================
        * Uncomment for library tests
        // test_vec_lib();
        // test_box_lib();
        // test_star_lib();
        // test_galaxy_lib();
        // test_quad_tree_lib();
    ======================================*/
}