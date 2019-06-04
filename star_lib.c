/*======================================
 * Galaxy Simulation using Quad-Trees
 * HEPIA 2018-2019 ITI 1
 * Sergey PLATONOV
 * star_lib.c
 * Library for star manipulations
======================================*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "vec_lib.h"
#include "star_lib.h"
#include <math.h>


star *new_star_vel(vec pos, vec vel, vec acc, double mass, double dt) {
    star* s = malloc(sizeof(star));
    s->acc = acc;
    s->mass = mass;
    s->pos_t = pos;                                     // p(t)
    s->pos_t_dt = *sub_vec(&pos, mul_vec(dt, &vel));    // p(t-δt)

    return s;
}

void reset_acceleration(star *s) {
    vec* zero = new_vec(0.0, 0.0);
    s->acc = *zero;
}

void update_acceleration(star *s, const star *const s2) {
    double mass_product = s->mass * s2->mass;
    double norm_Rij = distance(&(s->pos_t), &(s2->pos_t));
    vec* Rji = sub_vec(&(s2->pos_t), &(s->pos_t));
    double alpha = ((G * mass_product) * pow((norm_Rij + Epsilon), -3.0));
    vec* F_ij = mul_vec(alpha, Rji);
    s->acc = *mul_vec((1.0 / s->mass), F_ij);
}

void update_position(star *s, double dt) {
    vec tmp = s->pos_t;
    s->pos_t = *sub_vec(mul_vec(2.0, &s->pos_t), add_vec(&s->pos_t_dt, mul_vec(dt * dt, &s->acc)));
    s->pos_t_dt = tmp;

    //En pseudo-code cette mise à jour est de la forme:
    //pos_t = 2*pos_t - pos_t_dt + acc * dt * dt
}

void print_star(const star *const s) {
    printf("\n ----- STAR -----");
    printf("\n p(t) = \t");
    print_vec(&s->pos_t);
    printf("\n p(t-δt) = \t");
    print_vec(&s->pos_t_dt);
    printf("\n p\" = \t\t");
    print_vec(&s->acc);
    printf("\n mass = \t%g kg", s->mass);
}

void test_star_lib() {
//    printf("======= Star Library Tests ==============\n");
//    vec* p1 = new_vec(1.0, 1.0);
//    vec* p2 = new_vec(2.0, 2.0);
//    vec* v1 = new_vec(1.0, 1.0);
//    vec* v2 = new_vec(1.0, 1.0);
//    vec* a1 = new_vec(2.0, 2.0);
//    vec* a2 = new_vec(4.0, 2.0);
//    double m1 = 5.0;
//    double m2 = 50.0;
//    double dt = 1.0;
//
//    star* light_star = new_star_vel(*p1, *v1, *a1, m1, dt);
//    star* heavy_star = new_star_vel(*p2, *v2, *a2, m2, dt);
//    update_acceleration(light_star, heavy_star);
//
//    if(light_star->acc.x == 0.0 && light_star->acc.y == 0.0) {
//        printf(" update_acceleration() \t\t%s-- ok --%s \n", KGRN, KNRM);
//    }
//    if( four_boxes[1].x0 == 2.0 && four_boxes[1].x1 == 4.0
//        && four_boxes[1]. y0 == 0.0 && four_boxes[1].y1 == 4.0) {
//        printf(" divide_in_four() \t\t%s-- ok --%s \n", KGRN, KNRM);
//    }
//    if( l == 4.0 ) {
//        printf(" compute_length \t\t%s-- ok --%s \n", KGRN, KNRM);
//    }
//    printf("=======================================\n\n");
}
