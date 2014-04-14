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
#include <math.h>
#include <stdio.h>

void precompute_stiffness(double stiffness_mu, StiffnessDataContainer *StiffnessConstants){

    // The 'ideal' resting position of a face-pair.
    double N_A, N_B, N_C, N_D;
    N_A = N_B = N_C = N_D =  0.866025;

    StiffnessConstants->alpha_A = N_B/(N_A + N_B);
    StiffnessConstants->alpha_B = N_A/(N_A + N_B);
    StiffnessConstants->alpha_C = N_D/(N_C + N_D);
    StiffnessConstants->alpha_D = N_C/(N_C + N_D);

    // Evaluate lambda, the coefficient of stiffness
    StiffnessConstants->lambda = stiffness_mu * 
                                (2.0/3.0) * 
                                (N_A + N_B)/((N_A*N_B)*(N_A*N_B));


}

void runtime_stiffness(Particle verts[], FacePair facepairs[], int num_facepairs, StiffnessDataContainer *constants) {

    for (int i = 0; i < num_facepairs; i++){
        FacePair *facepair = &facepairs[i];

        double lambda = constants->lambda;

        vector *A = &(verts[facepair->A].pos);
        vector *B = &(verts[facepair->B].pos);
        vector *C = &(verts[facepair->C].pos);
        vector *D = &(verts[facepair->D].pos);

        // Evaluate bending vector R
        vector bending_vector = v_add(
            v_add(
                v_scalar_mul(*A, constants->alpha_A),
                v_scalar_mul(*B, constants->alpha_B)
            ),
            v_add(
                v_scalar_mul(*C, constants->alpha_C),
                v_scalar_mul(*D, constants->alpha_D)
            )
        );

        // Apply the bending forces to the particles
        vector force_A = v_scalar_mul(bending_vector, -lambda * constants->alpha_A);
        *A = v_add(*A, force_A);

        vector force_B = v_scalar_mul(bending_vector, -lambda * constants->alpha_B);
        *B = v_add(*B, force_B);

        vector force_C = v_scalar_mul(bending_vector, -lambda * constants->alpha_C);
        *C = v_add(*C, force_C);

        vector force_D = v_scalar_mul(bending_vector, -lambda * constants->alpha_D);
        *D = v_add(*D, force_D);

    }
}
