//
//  readin.c
//  Hyperbolic_C
//
//  Created by Lito Nicolai on 2/18/14.
//  Copyright (c) 2014 Lito Nicolai. All rights reserved.
//

#include <stdio.h>
#include "readin.h"

Particle* get_verts(void){
    size_t p_size;
    p_size = sizeof(Particle);
    
    FILE *f;
    f = fopen("verts", "r+");
    
    if( f == NULL){
        printf("No such file\n");
    }
    
    int i;
    for (i = 0; i < NUM_PARTICLES; i++){
        fread(&verts, p_size, 1, f);
    }
    
    fclose(f);
    return verts;
}

Edge* get_edges(void){
    size_t e_size;
    e_size = sizeof(Edge);
    
    FILE *f;
    f = fopen("edges", "r+");
    if( f == NULL){
        printf("No such file\n");
    }
    
    int i;
    for (i = 0; i < NUM_EDGES; i++){
        fread(&edges, e_size, 1, f);
    }
    
    fclose(f);
    return edges;
}