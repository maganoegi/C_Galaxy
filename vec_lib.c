/*======================================
 * Galaxy Simulation using Quad-Trees
 * HEPIA 2018-2019 ITI 1
 * Sergey PLATONOV
 * vec_lib.c
 * Library for basic vector manipulations
======================================*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "vec_lib.h"
#include <math.h>

vec* new_vec(double x, double y) {
    vec* v = malloc(sizeof(vec));
    v->x = x;
    v->y = y;

    return v;
}

vec* add_vec(const vec *const v1, const vec *const v2) {
    double x = v1->x + v2->x;
    double y = v1->y + v2->y;

    return new_vec(x, y);
}

vec* sub_vec(const vec *const v1, const vec *const v2) {
    double x = v1->x - v2->x;
    double y = v1->y - v2->y;

    return new_vec(x, y);
}

vec* mul_vec(double alpha, const vec *const v2) {
    double x = v2->x * alpha;
    double y = v2->y * alpha;

    return new_vec(x, y);
}

double norm(const vec *const v1) {
    double scalar;
    scalar = sqrt(pow(v1->x, 2) + pow(v1->y, 2));

    return scalar;
}

double distance(const vec *const v1, const vec *const v2) {
    vec* v3 = sub_vec(v1, v2);
    double d = norm(v3);

    return d;
}

void print_vec(const vec *const v) {
    // Apply Colors
    // Check for pretty formatting possibilities
    // Check if %g best display formatter for "double type"
    printf("(%g,%g)", v->x, v->y);
}

void vec_free(vec** v) {
    free(*v);
    *v = NULL;
}

void test_vec_lib() {
    printf("\n======= Vec Library Tests ==============\n");
    double x1 = 5.0;
    double y1 = 5.0;

    double x2 = 3.0;
    double y2 = 3.0;
    vec* v1 = new_vec(x1, y1);
    vec* v2 = new_vec(x2, y2);

    vec* v_added = add_vec(v1, v2);
    vec* v_subbed = sub_vec(v1, v2);
    vec* v_mulled = mul_vec(5.0, v1);
    double v1_norm = norm(v1);
    double d = distance(v1, v2);

    if( (v_added->x == 8.0) && (v_added->y == 8.0) ) {
        printf(" vector addition \t\t%s-- ok --%s \n", KGRN, KNRM);
    }
    if( (v_subbed->x == 2.0) && (v_subbed->y == 2.0) ) {
        printf(" vector substraction \t\t%s-- ok --%s \n", KGRN, KNRM);
    }
    if( (v_mulled->x == 25.0) && (v_mulled->y == 25.0) ) {
        printf(" vector multiplication \t\t%s-- ok --%s \n", KGRN, KNRM);
    }
    if( v1_norm == sqrt(50.0) ) {
        printf(" vector norm \t\t\t%s-- ok --%s \n", KGRN, KNRM);
    }
    if( d == sqrt(8.0) ) {
        printf(" intra-vector distance \t\t%s-- ok --%s \n", KGRN, KNRM);
    }


    printf("========================================\n\n");
}
