/*======================================
 * Galaxy Simulation using Quad-Trees
 * HEPIA 2018-2019 ITI 1
 * Sergey PLATONOV
 * quadtree_lib.h
 * Library for quadtree manipulations
======================================*/

#ifndef C_GALAXY_QUADTREE_LIB_C
#define C_GALAXY_QUADTREE_LIB_C

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "vec_lib.h"
#include "star_lib.h"
#include "box_lib.h"
#include "galaxy_lib.h"

typedef struct __node {
    struct __node *children[4];
    box b;
    star *s;
    star *super_s;
    int is_empty;
} node;

typedef struct __quad_tree {
    node* root;
} quad_tree;


quad_tree *create_quad_tree_from_galaxy(const galaxy *const g);
void free_quad_tree(quad_tree *t);
void test_quad_tree_lib();
void update_acceleration_from_node(const node *const n, star *s,
                                   double theta);
void update_accelerations_of_all_stars(const node *const n,
                                       galaxy *g, double theta);

#endif //C_GALAXY_QUADTREE_LIB_C