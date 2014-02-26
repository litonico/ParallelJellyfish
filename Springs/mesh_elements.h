//
//  mesh_elements.h
//  Hyperbolic_C
//
//  Created by Lito Nicolai on 2/4/14.
//
//

#ifndef Hyperbolic_C_mesh_elements_h
#define Hyperbolic_C_mesh_elements_h
#include "vectormath.h"

typedef struct {
    vector pos;
    vector prev_pos;
} Particle;

typedef struct {
    int a;
    int b;
    double length;
} Edge;

#endif

