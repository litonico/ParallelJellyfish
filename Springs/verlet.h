//
//  verlet.h
//  Hyperbolic_C
//
//  Created by Lito Nicolai on 2/19/14.
//  Copyright (c) 2014 Lito Nicolai. All rights reserved.
//

#ifndef Hyperbolic_C_verlet_h
#define Hyperbolic_C_verlet_h
#include "mesh_elements.h"

#define num_iterations 1

void jitter_x(Particle verts[], float coef, int num_verts);
void satisfy_constraints(Particle verts[], Edge edges[], int num_verts);
void resolve_collision(Particle verts[], Edge edges[], int num_edges);
void integrate_momentum(Particle verts[], Edge edges[], int num_verts);

#endif
