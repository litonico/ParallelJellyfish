//
//  verlet.c
//  Hyperbolic_C
//
//  Created by Lito Nicolai on 1/31/14.
//
//


#include <stdlib.h>
#include "vectormath.h"
#include "verlet.h"
#define num_iterations 1

vector gravity = {0.0, -0.01, 0.0};

void jitter_x(Particle verts[], float coef, int num_verts) {
    for (int i = 0; i < num_verts; i++) {
        float rndm = (rand() / (float) RAND_MAX) * (float) coef; 
        verts[i].pos.x += rndm;
        }
}


void apply_gravity(Particle verts[], int num_verts, float simulation_speed){
    
    // adds acceleration due to gravity to each vertex

    for (int i = 0; i < num_verts; i++) {
        vector *accel = &(verts[i].accel);
        *accel = v_add(*accel, gravity);
    }
}

void integrate_momentum(Particle verts[], int num_verts, float timestep, float simulation_speed){
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
        *x = v_add(v_add(*x, v_sub(*x, *prev_x)), 
                v_scalar_mul(verts[i].accel, timestep*timestep));
        //x += x - prev_x + accel*timestep^2
        *prev_x = temp; 
        // the contents of prev_x are set to be what was stored in temp
        
    }
}


void satisfy_constraints(Particle verts[], Edge edges[], int num_edges, float simulation_speed){
    // Iterates through the edges of the mesh
    // and moves vertices towards or away from
    // each other such that each edge converges
    // in length.
    
    for (int i = 0; i < num_iterations; i++) {
        for (int j = 0; j < num_edges; j++) {
            Edge* current_edge = &edges[j];
            double restlen = current_edge->length;
            

            vector* x1 = &(verts[current_edge->a].pos);
            vector* x2 = &(verts[current_edge->b].pos);

            vector length_vector = v_sub(*x2, *x1);

            double len = v_magnitude(length_vector);

            vector difference = v_scalar_mul(
                                        v_normalize(length_vector),
                                        ((restlen - len)/2.0)
                                    );
             
            *x2 = v_scalar_mul(v_add(*x2, v_scalar_mul(difference, simulation_speed)), verts[current_edge->b].invmass);
            *x1 = v_scalar_mul(v_sub(*x1, v_scalar_mul(difference, simulation_speed)), verts[current_edge->a].invmass);
                
        }
    }
};

void resolve_collision(Particle verts[], Edge edges[], int num_verts, float simulation_speed){
    
    // If the distance between any two particles is
    // less than some threshold, this function moves
    // them apart to avoid collisions. (Does not do
    // a perfect job- e.g. edge-edge intersection)
    
    double collide_dist = 1.0;

    for (int i = 0; i < num_verts; i++) {
        for (int j = i + 1; j < num_verts; j++){
            
            vector *x1 = &(verts[i].pos);
            vector *x2 = &(verts[j].pos);

            vector length_vector = v_sub(*x2, *x1);

            double len = v_magnitude(length_vector);

            if (len < collide_dist) {
                vector difference = v_scalar_mul(
                                        v_normalize(length_vector),
                                        ((collide_dist - len)/2.0)
                                        );

                *x2 = v_add(*x2, v_scalar_mul(difference, simulation_speed));
                *x1 = v_sub(*x1, v_scalar_mul(difference, simulation_speed));
                
            }
        }
    }
};

