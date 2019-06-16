/*======================================
 * Galaxy Simulation using Quad-Trees
 * HEPIA 2018-2019 ITI 1
 * Sergey PLATONOV
 * box_lib.c
 * Library for box manipulations
======================================*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "box_lib.h"
#include "vec_lib.h"
#include <math.h>

box new_box(double x0, double x1, double y0, double y1) {
    box b;
    b.x0 = x0;
    b.x1 = x1;
    b.y0 = y0;
    b.y1 = y1;

    return b;
}

box *divide_in_four(box b) {
    double dx = (b.x1 - b.x0)/2.0;
    double dy = (b.y1 - b.y0)/2.0;

    double x0 = b.x0;
    double x1 = x0 + dx;
    double x2 = b.x1;

    double y0 = b.y0;
    double y1 = y0 + dy;
    double y2 = b.y1;

    box* divided = malloc(4 * sizeof(box));
    divided[0].x0 = x0;
    divided[0].x1 = x1;
    divided[0].y0 = y0;
    divided[0].y1 = y1;

    divided[1].x0 = x1;
    divided[1].x1 = x2;
    divided[1].y0 = y0;
    divided[1].y1 = y1;

    divided[2].x0 = x0;
    divided[2].x1 = x1;
    divided[2].y0 = y1;
    divided[2].y1 = y2;

    divided[3].x0 = x1;
    divided[3].x1 = x2;
    divided[3].y0 = y1;
    divided[3].y1 = y2;

    return divided;
}

int is_inside(box b, vec v) {
    int result = 0;
    if ( (v.x >= b.x0) && (v.x <= b.x1) && (v.y >= b.y0) && (v.y <= b.y1)) {
        result = 1;
    }

    return result;
}

double compute_length(box b) {
    double n_s = b.x1 - b.x0;
    double e_w = b.y1 - b.y0;

    if (n_s >= e_w) {
        return n_s;
    } else {
        return e_w;
    }
}

void print_box(box b) {
    printf("\nBox x0 = %f, x1 = %f, y0 = %f, y1 = %f\n", b.x0, b.x1, b.y0, b.y1);
}


void test_box_lib() {
    printf("======= Box Library Tests ==============\n");
    box b = new_box(0.0, 4.0, 0.0, 8.0);
    vec* v_in = new_vec(2.0, 2.0);
    vec* v_out = new_vec(5.0, 5.0);
    int true = is_inside(b, *v_in);
    int false = is_inside(b, *v_out);
    box* four_boxes = divide_in_four(b);
    double l = compute_length(four_boxes[2]);

    if( true == 1 && false == 0 ) {
        printf(" is_inside() \t\t\t%s-- ok --%s \n", KGRN, KNRM);
    }
    if( four_boxes[1].x0 == 2.0 && four_boxes[1].x1 == 4.0
        && four_boxes[1]. y0 == 0.0 && four_boxes[1].y1 == 4.0) {
        printf(" divide_in_four() \t\t%s-- ok --%s \n", KGRN, KNRM);
    }
    if( l == 4.0 ) {
        printf(" compute_length \t\t%s-- ok --%s \n", KGRN, KNRM);
    }
    printf("========================================\n\n");
}
