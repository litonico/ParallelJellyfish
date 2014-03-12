//
//  vectormath.h
//  Hyperbolic_C
//
//  Created by Lito Nicolai on 2/4/14.
//
//



#ifndef Hyperbolic_C_vectormath_h
#define Hyperbolic_C_vectormath_h

typedef struct {
    double x, y, z;
} vector;


double v_dot(vector v1, vector v2);
vector v_add(vector v1, vector v2);
vector v_sub(vector v1, vector v2);
vector v_scalar_mul(vector v, double s);
double v_magnitude(vector v);
vector v_normalize(vector v);
#endif



