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
    int a;
    int b;
    double length;
} Edge;


#endif

