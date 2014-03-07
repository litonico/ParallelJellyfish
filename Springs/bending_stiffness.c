// Compute faces from edges
// Compute list of triangle pairs (possibly in python?)

// Bending stiffness
//
// void precompute_stiffness
// Compute each vertex normal in 'resting' position
//
// A_normal = v_cross(v_sub(A, C)
//
// For each triangle-pair, with outside verts A and B
// and inside verts C and D:
//      N_A = v_cross(v_sub(A, C), v_sub(A, D));
//      N_B = v_cross(v_sub(B, D), v_sub(B, C));
//      N_C = v_cross(v_sub(C, B), v_sub(C, A));
//      N_D = v_cross(v_sub(D, A), v_sub(D, B));
//      alpha_A = N(B)/(N(A) + N(B))
//      alpha_B = N(A)/(N(A) + N(B))
//      alpha_C = N(D)/(N(C) + N(D))
//      alpha_D = N(C)/(N(C) + N(D))
//
// Evaluate lambda
// l = 
// Evaluate the jacobian contribution
//
//
// void runtime_stiffness(void) {
// 
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
