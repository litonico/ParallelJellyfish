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
#include "verlet.c"
//#include "constants.h"

int main(int argc, const char * argv[])
{
    // Allocate memory for arrays of verts and edges
    Particle* p = (Particle *) calloc(NUM_PARTICLES, sizeof(Particle[NUM_PARTICLES]));
    p = get_verts();

    Edge* e = (Edge *) calloc(NUM_EDGES, sizeof(Edge[NUM_EDGES]));
    e = get_edges();

    // Fill those arrays by looping through the verts and edges files

    FILE *f;
    f = fopen("verts", "r+");

    if( f == NULL){
        printf("No such file\n");
        exit(-1);
    }

    for (int i = 0; i < NUM_PARTICLES; i++){
        fscanf(f, "%f %f %f", p[i]->pos.x, p[i]->pos.y, p[i]->pos.z)
    }


    
    
    
//    integrate_momentum(p, e, NUM_PARTICLES);
//    satisfy_constraints(p, e, NUM_EDGES);
//    resolve_collision(p,e, NUM_PARTICLES);
    return 0;
}

