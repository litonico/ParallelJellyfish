#ifndef bending_stiffness_h
#define bending_stiffness_h

typedef struct {
    int A, B, C, D; // vertex numbers
    double alpha_A, alpha_B, alpha_C, alpha_D;
    double lambda;
    // Jacobian matrix?
} FacePair;

void runtime_stiffness(FacePair[] facepairs);


#endif
