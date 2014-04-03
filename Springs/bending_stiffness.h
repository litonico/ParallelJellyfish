#ifndef bending_stiffness_h
#define bending_stiffness_h
#include "mesh_elements.h"

double N_A, N_B, N_C, N_D;

typedef struct {
    int A, B, C, D; // vertex numbers
    double alpha_A, alpha_B, alpha_C, alpha_D;
    double lambda;
    // Jacobian matrix?
} FacePair;

void precompute_stiffness(Particle verts[], FacePair facepairs[]);

void runtime_stiffness(FacePair[] facepairs, double lambda);


#endif
