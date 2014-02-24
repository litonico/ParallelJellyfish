//
//  vectormath.c
//  Hyperbolic_C
//
//  Created by Lito Nicolai on 2/19/14.
//  Copyright (c) 2014 Lito Nicolai. All rights reserved.
//

#include <stdio.h>
#include "vectormath.h"
#include <math.h>

double vdot(vector v1, vector v2){
    double ret;
    ret += v1.x * v2.x;
    ret += v1.y * v2.y;
    ret += v1.z * v2.z;
    
    return ret;
}

vector v_add(vector v1, vector v2){
    vector ret;
    ret.x = v1.x + v2.x;
    ret.y = v1.y + v2.y;
    ret.z = v1.z + v2.z;
    
    return ret;
}

vector v_sub(vector v1, vector v2){
    vector ret;
    ret.x = v1.x - v2.x;
    ret.y = v1.y - v2.y;
    ret.z = v1.z - v2.z;
    
    return ret;
}

vector v_scalar_mul(vector v, double s){
    vector ret;
    ret.x = v.x * s;
    ret.y = v.x * s;
    ret.z = v.z * s;
    
    return ret;
}

double v_magnitude(vector v){
    double ret;
    ret = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    return ret;
}