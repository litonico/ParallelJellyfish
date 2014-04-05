// Bending Stiffness
// See: Simple Linear Bending Stiffness in Particle Systems, 
// Volino and Magnenat-Thalmann.
//
// Major changes to the paper's algorithm allow it to work
// with a mesh of changing shape. Storing constant alpha-values
// allow us to assume a final shape of the mesh, and aim for that,
// instead of re-evaluating the alphas at every step. That's only
// possible because we're assume that each face of the mesh will
// end up as an equilateral triangle; otherwise, no luck.

#include "bending_stiffness.h"

struct StiffnessData precompute_stiffness(double stiffness_mu){

    StiffnessDataContainer StiffnessConstants; 

    N_A = v_magnitude(v_cross(v_sub(A, C), v_sub(A, D)));
    N_B = v_magnitude(v_cross(v_sub(B, D), v_sub(B, C)));
    N_C = v_magnitude(v_cross(v_sub(C, B), v_sub(C, A)));
    N_D = v_magnitude(v_cross(v_sub(D, A), v_sub(D, B)));
    StiffnessConstants->alpha_A = N(B)/(N(A) + N(B))
    StiffnessConstants->alpha_B = N(A)/(N(A) + N(B))
    StiffnessConstants->alpha_C = N(D)/(N(C) + N(D))
    StiffnessConstants->alpha_D = N(C)/(N(C) + N(D))

    // Evaluate lambda, the coefficient of stiffness
    StiffnessConstants->lambda = edgelen * 
                                 stiffness_mu * 
                                 (2.0/3.0) * 
                                 (N_A + N_B)/((N_A*N_B)*(N_A*N_B));

    return StiffnessConstants

}

void runtime_stiffness(Particle verts[], FacePair facepairs[], double lambda) {

    for (int i = 0; i < num_facepairs; i++){
        FacePair *facepair = &facepairs[i];

        double lambda = facepair->lambda; // probably should be a global

        vector *A = &(verts[facepair->A].pos);
        vector *B = &(verts[facepair->B].pos);
        vector *C = &(verts[facepair->C].pos);
        vector *D = &(verts[facepair->D].pos);

        // Evaluate bending vector R
        vector bending_vector = v_add(
            v_add(
                v_scalar_mul(A, alpha_A)
                v_scalar_mul(B, alpha_B)
            ),
            v_add(
                v_scalar_mul(C, alpha_C),
                v_scalar_mul(D, alpha_D)
            )
        );

        // Apply the bending forces to the particles
        force_A = v_scalar_mul(bending_vector, -lambda * facepair->alpha_A)
        *A = v_add(*A, force_A)

        force_B = v_scalar_mul(bending_vector, -lambda * facepair->alpha_B)
        *B = v_add(*B, force_B)

        force_C = v_scalar_mul(bending_vector, -lambda * facepair->alpha_C)
        *C = v_add(*C, force_C)

        force_D = v_scalar_mul(bending_vector, -lambda * facepair->alpha_D)
        *D = v_add(*D, force_D)

    }
}
