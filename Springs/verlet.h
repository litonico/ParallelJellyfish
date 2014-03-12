//
//  verlet.h
//  Hyperbolic_C
//
//  Created by Lito Nicolai on 2/19/14.
//  Copyright (c) 2014 Lito Nicolai. All rights reserved.
//

#ifndef verlet_h
#define verlet_h
#include "mesh_elements.h"

void apply_gravity(Particle verts[], int num_verts);
void integrate_momentum(Particle verts[], int num_verts, float timestep);
void jitter_x(Particle verts[], float coef, int num_verts);
void satisfy_constraints(Particle verts[], Edge edges[], int num_edges, float coefficient);
void resolve_collision(Particle verts[], Edge edges[], int num_edges);

#endif
