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
    if(is_inside(n->b, s->pos_t) && n != NULL) {
        if(n->children == NULL) {
            if(n->is_empty) {
                n->is_empty = 0;
                n->s = s;
            } else {
                box* kids = divide_in_four(n->b);
                node* next_four = malloc(4 * sizeof(node));
                for(int i = 0; i < 4; i++) {

                }
            }
        }
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

}

