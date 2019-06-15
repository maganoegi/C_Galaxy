/*======================================
 * Galaxy Simulation using Quad-Trees
 * HEPIA 2018-2019 ITI 1
 * Sergey PLATONOV
 * vec_lib.h
 * Library for basic vector manipulations
======================================*/

#ifndef C_GALAXY_VEC_LIB_C
#define C_GALAXY_VEC_LIB_C

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

typedef struct __vec {
    double x,y;
} vec;

vec* new_vec(double x, double y);
vec* add_vec(const vec *const v1, const vec *const v2);
vec* sub_vec(const vec *const v1, const vec *const v2);
vec* mul_vec(double alpha, const vec *const v2);
double norm(const vec *const v1);
double distance(const vec *const v1, const vec *const v2);
void print_vec(const vec *const v);
void vec_free(vec* v);

void test_vec_lib();

#endif //C_GALAXY_VEC_LIB_C