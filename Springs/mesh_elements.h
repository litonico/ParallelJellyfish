#ifndef mesh_elements_h
#define mesh_elements_h
#include "vectormath.h"

typedef struct {
    vector pos;
    vector prev_pos;
    vector accel;
    float invmass;
} Particle;

typedef struct {
    int a, b;
    double length;
} Edge;

typedef struct {
    int v1, v2, v3;
} Face;

#endif

