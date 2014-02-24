#include <stdlib.h>
#include <stdio.h>
#include "mesh_elements.h"
#include "verlet.c"


/*
void integrate_momentum(Particle verts[], Edge edges[]){
    
    for (int i = 0; i < NUM_PARTICLES; i++) {
        vector *x = &(verts[i].pos); 
        vector temp = *x; 
        vector *prev_x = &(verts[i].prev_pos); 
        *x = v_add(*x, v_sub(*x, *prev_x)); 
        *prev_x = temp; 
        
    }
}
*/


int main(void){
    // allocated on the stack instead of the heap
    // (so I can more easily understand what's happening)
    Particle verts[2] = {{{1,1,1},{1,1,1}}, {{5,4,2},{5,4,2}}};
    Edge edges[] = {{0,1,1.0}};

    integrate_momentum(verts, edges, NUM_PARTICLES);
    satisfy_constraints(verts, edges, NUM_EDGES);
    // resolve_collision(verts, edges);

    printf("%f\n",v_magnitude(v_sub(verts[0].pos, verts[1].pos)));

    return 0;
}
