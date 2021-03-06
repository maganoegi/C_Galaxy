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
#include "gfx.h"
#include <SDL2/SDL.h>

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

void show_pixels(galaxy* g, struct gfx_context_t* context, double scale, int screen_dimension) {
    // Clear Color
    gfx_clear(context, COLOR_BLACK);

    for(int i = 0; i < g->num_bodies; i++) {
        /*=========================================================================
            * Color generation proportional to mass (BLUE -> RED)
        =========================================================================*/
        double mass_ratio = g->stars[i]->mass / MAXMASS;
        mass_ratio = mass_ratio * pow(10.0, -21.0);
        int red = (int)(255.0 * mass_ratio);
        int green = 0;
        int blue = (int)(255.0 * (1.0 - mass_ratio));
        uint32_t color = MAKE_COLOR(red, green, blue);

        /*=========================================================================
            * Dimension scaling
        =========================================================================*/
        double size_scale = (2.0 * scale) / (double)screen_dimension;
        double pos_x_rel = g->stars[i]->pos_t.x + scale;
        double pos_y_rel = g->stars[i]->pos_t.y + scale;

        int px = (int)(pos_x_rel / size_scale);
        int py = (int)(pos_y_rel / size_scale);

        if((px < 0) || (py < 0)) { // Protection against px,py overflow when double -> int
            px = 0;
            py = 0;
        }
        gfx_putpixel(context, px, py, color);
    }
    gfx_present(context);
    sleep(0.0001);
}

int main(int argc, char **argv) {
    input_error_handler(argc, argv);

    /*=========================================================================
        * Initialization
    =========================================================================*/
    int num_stars = atoi(argv[1]);
    double theta = atof(argv[2]);
    srand(time(NULL)); // seed for rng

    int iter = 1000000; // number of temporal iterations
    double scale = 1000000000500000005.0; // Empirically chosen scale
    box domain = new_box(
            -1.0 * scale, // x0
            1.0 * scale,  // x1
            -1.0 * scale, // y0
            1.0 * scale   // y1
            );

    /*=========================================================================
        * Initialization SDL
    =========================================================================*/
    int screen_dimension = 1000;
    struct gfx_context_t* context = gfx_create("Galaxy", screen_dimension, screen_dimension);
    if(!context) {
        fprintf(stderr, "\n--- Graphic mode init failed ---\n");
        EXIT_FAILURE;
    }
    SDL_ShowCursor(SDL_ENABLE); // To see the cursor
    SDL_Keycode key_pressed = 0; // ESC key

    /*=========================================================================
        * Galaxy Simulation
    =========================================================================*/
    galaxy* g = create_and_init_galaxy(num_stars, domain, 0.0);
    for(int i = 0; i < iter; i++) {
        SDL_PumpEvents();
        double dt = (double)i * time_unit;
        key_pressed = gfx_keypressed();
        if(key_pressed == SDLK_ESCAPE) {
            break;
        }
        resize_galaxy(g);
        show_pixels(g, context, scale, screen_dimension);
        reset_accelerations(g);
        quad_tree* qt = create_quad_tree_from_galaxy(g);
        update_accelerations_of_all_stars(qt->root, g, theta);
        update_positions(g, dt);
        free_quad_tree(qt);
    }
    gfx_destroy(context);
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