//
//  main.c
//  Hyperbolic_C
//
//  Created by Lito Nicolai on 2/6/14.
//  Copyright (c) 2014 Lito Nicolai. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "mesh_elements.h"
#include "readin.h"
#include "verlet.h"

int main(int argc, const char * argv[])
{
    Particle* p = (Particle *) calloc(NUM_PARTICLES, sizeof(Particle[NUM_PARTICLES]));
    p = get_verts();
    
    Edge* e = (Edge *) calloc(NUM_EDGES, sizeof(Edge[NUM_EDGES]));
    e = get_edges();
    
    //printf(p);
    
//    integrate_momentum(p, e);
//    satisfy_constraints(p, e);
//    resolve_collision(p,e);
    return 0;
}

