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
    if(n && is_inside(n->b, s->pos_t)) {
        if(!n->children[0] && !n->children[1] && !n->children[2] && !n->children[3]) {
            if(n->is_empty) {
                n->is_empty = 0;
                n->s = s;
            } else {
                box* kids = divide_in_four(n->b);
                
                for(int i = 0; i < 4; i++) {
                    n->children[i] = malloc(sizeof(node));
                    if(!n->children[i]) {
                        fprintf(stderr, "\nmalloc failed\n");
                        EXIT_FAILURE;
                    }
                    n->children[i]->b = kids[i];
                    n->children[i]->is_empty = 1;
                    n->children[i]->s = malloc(sizeof(star));
                    n->children[i]->super_s = malloc(sizeof(star));

                    for(int j = 0; j < 4; j++) {
                        n->children[i]->children[j] = NULL;
                    }

                    insert_star(n->children[i], n->s);

                }

                for(int i = 0; i < 4; i++) {
                    insert_star(n->children[i], s);
                }
                n->s = NULL;
                n->is_empty = 1;
            }
        } else {
            // Increment super star mass
            //printf("\nBEFORE supermass = %g, mass = %g\n", n->super_s->mass, s->mass);
            n->super_s->mass += s->mass;

            // Increment Center of mass coordinates
            n->super_s->pos_t_dt = n->super_s->pos_t;
            n->super_s->pos_t = *mul_vec((1.0 / n->super_s->mass), mul_vec(s->mass, add_vec(&n->super_s->pos_t, &s->pos_t)));

            for(int i = 0; i < 4; i++) {
                insert_star(n->children[i], s);
            }
        }
    }
}

quad_tree *create_quad_tree_from_galaxy(const galaxy *const g) {
    // Initialization quad-tree
    box boundaries = g->b;
    node* top = malloc(sizeof(node));
    top->s = NULL;
    top->super_s = g->stars[0];
    top->is_empty = 1;
    top->b = boundaries;
    for(int j = 0; j < 4; j++) {
        top->children[j] = NULL;
    }
    quad_tree* qt = malloc(sizeof(quad_tree));
    qt->root = top;

    // Populate the tree
    for(int i = 1; i < g->num_bodies; i++) {
        insert_star(qt->root, g->stars[i]);
    }

    return qt;
}

void free_node(node* n) {
    if(!n) return;

    for(int i = 0; i < 4; ++i) {
        free_node(n->children[i]);
    }
    free(n);
}

void free_quad_tree(quad_tree* qt) {
    free_node(qt->root);
    free(qt);
}

void update_acceleration_from_node(const node *const n, star *s, double theta) {
    //1. Si le nœud est une feuille non-vide et que l’étoile n’est pas dans le sousdomaine du nœud, on met à jour l’accélération entre l’étoile et l’étoile
    //contenue dans le nœud.
    if((!n->children[0]) && (!n->children[1]) && (!n->children[2]) && (!n->children[3])
    && (!n->is_empty) && !is_inside(n->b, s->pos_t)) {
        update_acceleration(s, n->s);
    } else if (compute_length(n->b) / (norm(sub_vec(&(n->super_s->pos_t), &(s->pos_t)))) < theta) {
        update_acceleration(s, n->super_s);
    } else {
        for (int i = 0; i < 4; i++) {
            if (n->children[i] != NULL) {
                update_acceleration_from_node(n->children[i], s, theta);
            }
        }
    }


    //2. Sinon, si n est assez éloigné de s (si la taille du sous-domaine de n divisée
    //par la distance entre la position de la super étoile de n et s est plus petite
    //que theta) on met à jour l’accélération de s à l’aide de la super étoile de
    //n.
    //3. Sinon, pour tous les enfants de n, on rappelle
    //update_acceleration_from_node(n, s, theta);
}

void update_accelerations_of_all_stars(const node *const n, galaxy *g, double theta) {
    for(int i = 0; i < g->num_bodies; i++) {
        update_acceleration_from_node(n, g->stars[i], theta);
    }
}

void test_quad_tree_lib() {

    box boundaries = new_box(-15.0, 15.0, -15.0, 15.0);
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
    top->b = boundaries;
    for(int j = 0; j < 4; j++) {
        top->children[j] = NULL;
    }


    // Stars to be inserted
    for(int i = 0; i < 30; i++) {
        printf("\nATTEMPT TO INSERT --------------------------------------------\n");
        insert_star(top, my_stars[i]);
//        print_star(my_stars[i]);
    }

    galaxy* g = create_and_init_galaxy(10, new_box(-100000000000000000000000.0, 100000000000000000000000.0, -100000000000000000000000.0, 100000000000000000000000.0), 1.0 * time_unit);
    quad_tree* qt = create_quad_tree_from_galaxy(g);
    update_accelerations_of_all_stars(qt->root, g, 0.1);
    printf("\nEND\n");
}

