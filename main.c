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
        fprintf(stderr, "%s\n========== Invalid Parameters Error ===========\n%s"
                        "%s  Please provide exactly 2 arguments%s\n"
                        "%s  └> (int)Number of stars, and (double)Theta %s\n"
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
    /*=========================================================================
        * Initialization
    =========================================================================*/
    int num_stars = atoi(argv[1]);
    double theta = atof(argv[2]);
    srand(time(NULL)); // seed for rng

    int iter = 100000; // number of temporal iterations
    double scale = pow(10.0, 20.0);
    box domain = new_box(
            -1.0 * scale, // x0
            1.0 * scale,  // x1
            -1.0 * scale, // y0
            1.0 * scale   // y1
            );

    /*=========================================================================
        * Galaxy Simulation
    =========================================================================*/
    galaxy* g = create_and_init_galaxy(num_stars, domain, 0.0);
    for(int i = 0; i < iter; i++) {
//        printf("%d / %d\n", i + 1, iter);
        print_vec(&g->stars[1]->pos_t);
//        printf("\nX = %g     Y = %g                 X = %g     Y = %g\n", g->stars[1]->pos_t.x * pow(10,-17.0), g->stars[1]->pos_t.y * pow(10,-17.0), g->stars[7]->pos_t.x * pow(10,-17.0), g->stars[7]->pos_t.y * pow(10,-17.0));
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
    printf("\n--- END ---\n");

    /*=========================================================================
        * Uncomment for library tests
    =========================================================================*/
        // test_vec_lib();
        // test_box_lib();
        // test_star_lib();
        // test_galaxy_lib();
        // test_quad_tree_lib();
}