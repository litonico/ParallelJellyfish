#ifndef bending_stiffness_h
#define bending_stiffness_h
#include "mesh_elements.h"


// Long name, but harmless; a struct to store const data
// about the stiffness of the mesh
typedef struct {
    double alpha_A, alpha_B, alpha_C, alpha_D;
    double lambda;
} StiffnessDataContainer;

void precompute_stiffness(
        double stiffness_mu, 
        StiffnessDataContainer *StiffnessConstants
        );

void runtime_stiffness(
        Particle verts[], 
        FacePair facepairs[], 
        int num_facepairs, 
        StiffnessDataContainer *constants
        );

#endif
