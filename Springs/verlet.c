//
//  verlet.c
//  Hyperbolic_C
//
//  Created by Lito Nicolai on 1/31/14.
//
//


#include "vectormath.c"
#include "verlet.h"
#include "constants.h"


void integrate_momentum(Particle verts[], Edge edges[], int num_verts){
    // For each vertex, calculates its change in 
    // position based on Verlet integration
    
    for (int i = 0; i < num_verts; i++) {
        vector *x = &(verts[i].pos); 
        //x points to the address of pos (a vector) of 
        //the i'th elem. of verts
        vector temp = *x; 
        // declared on the heap, has the contents of x (a vector)
        vector *prev_x = &(verts[i].prev_pos); 
        // points to the prev_pos of the i'th elem. of verts
        
        // ! tODO: acceleration !
        *x = v_add(*x, v_sub(*x, *prev_x)); // contents of x are:
        //x += x - prev_x + accel*timestep^2
        
        *prev_x = temp; 
        // the contents of prev_x are set to be what was stored in temp
        
    }
}


void satisfy_constraints(Particle verts[], Edge edges[], int num_edges){
    
    // Iterates through the edges of the mesh
    // and moves vertices towards or away from
    // each other such that each edge converges
    // in length.
    
    for (int i = 0; i < num_iterations; i++) {
        for (int j = 0; j < num_edges; j++) {
            Edge* current_edge = &edges[j];
            vector* x1 = &(verts[current_edge->a].pos);
            vector* x2 = &(verts[current_edge->b].pos);
            vector dir_vector = v_sub(*x1, *x2);
            double len = v_magnitude(dir_vector);
            vector difference = v_scalar_mul(
                                            dir_vector,
                                            ((restlen - len)/2.0)
                                            );
            verts[i].pos = v_add(*x2, difference);
            verts[j].pos = v_sub(*x1, difference);
                
        }
    }
};

void resolve_collision(Particle verts[], Edge edges[], int num_verts){
    
    // If the distance between any two particles is
    // less than some threshold, this function moves
    // them apart to avoid collisions. (Does not do
    // a perfect job- e.g. edge-edge intersection)
    
    for (int i = 0; i < NUM_PARTICLES; i++) {
        for (int j = i; j < NUM_PARTICLES; j++){
            vector *x1 = &(verts[i].pos);
            vector *x2 = &(verts[j].pos);
            vector dir_vector = v_sub(*x1, *x2);
            double len = v_magnitude(dir_vector);
            if (len < collide_dist) {
                vector difference = v_scalar_mul(
                                        dir_vector,
                                        ((collide_dist - len)/2.0)
                                        );
                verts[i].pos = v_add(*x2, difference);
                verts[j].pos = v_add(*x2, difference);
                
            }
        }
    }
};

