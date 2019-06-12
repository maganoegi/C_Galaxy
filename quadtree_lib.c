/*======================================
 * Galaxy Simulation using Quad-Trees
 * HEPIA 2018-2019 ITI 1
 * Sergey PLATONOV
 * quadtree_lib.c
 * Library for quadtree manipulations
======================================*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "vec_lib.h"
#include "star_lib.h"
#include "galaxy_lib.h"
#include "box_lib.h"
#include "quadtree_lib.h"
#include <math.h>
#include <time.h>


void insert_star(node* n, star* s) {
    if(is_inside(n->b, s->pos_t)) {
        if((n->children[0] == NULL) && (n->children[1] == NULL) && (n->children[2] == NULL) && (n->children[3] == NULL)) {
            if(n->is_empty) {
                printf("EMPTY LEAF\n\t");
                n->is_empty = 0;
                n->s = s;
            } else {
                printf("DIVISION\n\t");
                box* kids = divide_in_four(n->b);
                node* next_four = malloc(4 * sizeof(node));
                for(int i = 0; i < 4; i++) {
                    next_four[i].b = kids[i];
                    next_four[i].is_empty = 1;
                    next_four[i].s = malloc(sizeof(star));
                    next_four[i].super_s = malloc(sizeof(star));
                    for(int j = 0; j < 4; j++) {
                        next_four[i].children[j] = NULL;
                    }
                    insert_star(&next_four[i], n->s);
                }
                for(int i = 0; i < 4; i++) {
                    insert_star(&next_four[i], s);
                }
                n->s = NULL;
                n->is_empty = 1;
            }
        } else {
            printf("NODE\n\t");
            // Increment super star mass
            n->super_s->mass += s->mass;

            // Increment Center of mass coordinates
            n->super_s->pos_t_dt = n->super_s->pos_t;
            add_vec(&n->super_s->pos_t, &s->pos_t);

            for(int i = 0; i < 4; i++) {
                insert_star(n->children[i], s);
            }
        }
    } else {
        printf("NOT INSIDE\n");
    }
}

quad_tree *create_quad_tree_from_galaxy(const galaxy *const g) {

}

void free_quad_tree(quad_tree *t) {

}

void update_acceleration_from_node(const node *const n, star *s, double theta) {

}

void update_accelerations_of_all_stars(const node *const n, galaxy *g, double theta) {

}

void test_quad_tree_lib() {
    box boundaries = new_box(-4.0, 4.0, -4.0, 4.0);
    star** my_stars = malloc(30 * sizeof(star*));
    for(int i = 0; i < 30; i++) {
        my_stars[i] = malloc(sizeof(star));
        my_stars[i]->pos_t = *new_vec(0.5 + (double)i, 0.5 + (double)i);
        my_stars[i]->pos_t_dt = *new_vec(0.5 + (double)i, 0.5 + (double)i);
        my_stars[i]->mass = 20.0;
        my_stars[i]->acc = *new_vec(0.5 + (double)i, 0.5 + (double)i);
    }


    // Initialization node
    node* top = malloc(sizeof(node));
    top->s = NULL;
    top->super_s = my_stars[0];
    top->is_empty = 1;
    for(int j = 0; j < 4; j++) {
        top->children[j] = NULL;
    }

    top->b = boundaries;

    // Stars to be inserted
    for(int i = 0; i < 30; i++) {
        printf("\nATTEMPT TO INSERT --------------------------------------------\n");
        insert_star(top, my_stars[i]);
//        print_star(my_stars[i]);
    }
}

