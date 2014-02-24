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


double vdot();
vector vadd();
vector vsub();
vector vscalar_mul();
double vmagnitude();
#endif



