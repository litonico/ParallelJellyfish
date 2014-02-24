//
//  readin.h
//  Hyperbolic_C
//
//  Created by Lito Nicolai on 2/19/14.
//  Copyright (c) 2014 Lito Nicolai. All rights reserved.
//

#ifndef Hyperbolic_C_readin_h
#define Hyperbolic_C_readin_h
#include "mesh_elements.h"
#include "constants.h"

Particle verts[NUM_PARTICLES];
Edge edges[NUM_EDGES];

Particle* get_verts(void);
Edge* get_edges(void);

#endif
