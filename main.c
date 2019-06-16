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
#include <unistd.h>
//#include "gfx.h"
//#include <SDL2/SDL.h>

#include "vec_lib.h"
#include "star_lib.h"
#include "quadtree_lib.h"
#include "galaxy_lib.h"
#include "box_lib.h"

#define MAXMASS m_min + (10.0 * m_solar)

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

//void show_pixels(galaxy* g, struct gfx_context_t* context, double scale, int screen_dimension) {
    // Clear Color
//    gfx_clear(context, COLOR_BLACK);

//    for(int i = 0; i < g->num_bodies; i++) {
        //double mass_ratio = g->stars[i]->mass / MAXMASS;
        //mass_ratio = mass_ratio * pow(10.0, -21.0);
        //printf("\n%g\n", mass_ratio);
        //int red = (int)(255.0 * mass_ratio);
        //int green = 0;
        //int blue = (int)(255.0 * (1.0 - mass_ratio));
        //printf("\nr = %d, g = %d, b = %d\n", red, green, blue);

        //uint32_t color = MAKE_COLOR(red, green, blue);
//        uint32_t color = MAKE_COLOR(255, 255, 255);


//        double size_scale = (2.0 * scale) / (double)screen_dimension;
        //size_scale = size_scale * pow(10.0, -20.0);
//        printf("\nscale screen%g\n", size_scale);
//        double pos_x_rel = g->stars[i]->pos_t.x + scale;
//        double pos_y_rel = g->stars[i]->pos_t.y + scale;
//        printf("\npre = %g,    pre = %g\n", g->stars[i]->pos_t.x , g->stars[i]->pos_t.y );
//        printf("\npre px = %g,    pre py = %g\n", pos_x_rel , pos_y_rel );


//        int px;
//        int py;

//        if(((pos_x_rel / size_scale) < 0.0) || (pos_x_rel / size_scale) > 2147483640.0) {
//            px = 600;
//            py = 600;
//        } else {
//            px = (int)(pos_x_rel / size_scale);
//            py = (int)(pos_y_rel / size_scale);
//        }

        //printf("\nAAAAAAAA %g\n", pos_x_rel / size_scale);
        //printf("\npx = %d,    py = %d, iter = %d\n", px , py, i);


//        gfx_putpixel(context, px, py, color);

//    }

//    gfx_present(context);
//    sleep(0.001);
//}

int main(int argc, char **argv) {
    input_error_handler(argc, argv);



    /*=========================================================================
        * Initialization
    =========================================================================*/
    int num_stars = atoi(argv[1]);
    double theta = atof(argv[2]);
    srand(time(NULL)); // seed for rng

    int iter = 10000; // number of temporal iterations
    double scale = 1000000000000000000.0; // 18
    box domain = new_box(
            -1.0 * scale, // x0
            1.0 * scale,  // x1
            -1.0 * scale, // y0
            1.0 * scale   // y1
            );

    /*=========================================================================
        * Initialization SDL
    =========================================================================*/
//    int screen_dimension = 1000;
//    struct gfx_context_t* context = gfx_create("Galaxy", screen_dimension, screen_dimension);
//    if(!context) {
//        fprintf(stderr, "\n--- Graphic mode init failed ---\n");
//        EXIT_FAILURE;
//    }

//    SDL_ShowCursor(SDL_ENABLE); // To see the cursor
//    SDL_Keycode key_pressed = 0; // ESC key

    /*=========================================================================
        * Galaxy Simulation
    =========================================================================*/
    galaxy* g = create_and_init_galaxy(num_stars, domain, 0.0);
    for(int i = 0; i < iter; i++) {
//        SDL_PumpEvents();
        double dt = (double)i * time_unit;
//        key_pressed = gfx_keypressed();
//        if(key_pressed == SDLK_ESCAPE) {
//            return;
//        }
        resize_galaxy(g);
//        show_pixels(g, context, scale, screen_dimension);
        reset_accelerations(g);
        quad_tree* qt = create_quad_tree_from_galaxy(g);
        update_accelerations_of_all_stars(qt->root, g, theta);
        update_positions(g, dt);
        free_quad_tree(qt);
        for(int k = 0; k < g->num_bodies; k++) {
            printf("\niteration = %d/%d    number elements = %d\n", i, iter, g->num_bodies);
            print_vec(&g->stars[k]->pos_t);
        }
    }
//    gfx_destroy(context);
    free_galaxy(g);
    printf("END");
    return EXIT_SUCCESS;

    /*=========================================================================
        * Uncomment for library tests
    =========================================================================*/
        // test_vec_lib();
        // test_box_lib();
        // test_star_lib();
        // test_galaxy_lib();
        // test_quad_tree_lib();
}