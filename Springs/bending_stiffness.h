#ifndef bending_stiffness_h
#define bending_stiffness_h
#include "mesh_elements.h"


// Long name, but harmless; a struct to store const data
// about the stiffness of the mesh
typedef struct {
    const double alpha_A, alpha_B, alpha_C, alpha_D;
    const double lambda;
} StiffnessDataContainer;

void precompute_stiffness(Particle verts[], FacePair facepairs[]);

void runtime_stiffness(FacePair[] facepairs, double lambda);


#endif
