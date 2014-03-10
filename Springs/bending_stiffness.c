// Compute faces from edges
// Compute list of triangle pairs (possibly in python?)

// Bending stiffness
//
#include "bending_stiffness.h"

void precompute_stiffness(FacePair facepairs[]){
    
    // Populate array of FacePairs
    // with appropriate data

    for (int i = 0; i < num_facepairs; i++){
        N_A = v_magnitude(v_cross(v_sub(A, C), v_sub(A, D)));
        N_B = v_magnitude(v_cross(v_sub(B, D), v_sub(B, C)));
        N_C = v_magnitude(v_cross(v_sub(C, B), v_sub(C, A)));
        N_D = v_magnitude(v_cross(v_sub(D, A), v_sub(D, B)));
        facepairs->alpha_A = N(B)/(N(A) + N(B))
        facepairs->alpha_B = N(A)/(N(A) + N(B))
        facepairs->alpha_C = N(D)/(N(C) + N(D))
        facepairs->alpha_D = N(C)/(N(C) + N(D))

        // Evaluate lambda
        facepairs->l = (2.0/3.0) * (N_A + N_B)/((N_A*N_B)*(N_A*N_B))
    }
}

void runtime_stiffness(void) {
    
    // Evaluate bending vector R
    vector bending_vector = v_add(
        v_add(
            scalar_mul(A, alpha_A)
            scalar_mul(B, alpha_B)
        ),
        v_add(
            scalar_mul(C, alpha_C),
            scalar_mul(D, alpha_D)
    );

// evaluate particle forces
// F_A
// F_B
// F_C
// F_D
}
