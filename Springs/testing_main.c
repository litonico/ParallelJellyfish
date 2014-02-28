#include <stdlib.h>
#include <stdio.h>
#include "mesh_elements.h"
#include "verlet.c"


int main(void){
    // allocated on the stack instead of the heap
    // (so I can more easily understand what's happening)
    Particle verts[2] = {{{1,1,1},{1,1,1}}, {{5,4,2},{5,4,2}}};
    Edge edges[] = {{0,1,1.0}};

    // Test satistfy_constraints
    printf("Original len: %f\n",
            v_magnitude(v_sub(verts[0].pos, verts[1].pos)));

    satisfy_constraints(verts, edges, NUM_EDGES);

    printf("Corrected len: %f\n",
            v_magnitude(v_sub(verts[0].pos, verts[1].pos)));

    // integrate_momentum(verts, edges, NUM_PARTICLES);

    vector movetest = {-1, -1, -1};
    verts[1].pos = v_add(verts[1].pos, movetest);

    printf("initial len: %f\n",
            v_magnitude(v_sub(verts[0].pos, verts[1].pos)));

    resolve_collision(verts, edges, 2);

    printf("Corrected len: %f\n",
            v_magnitude(v_sub(verts[0].pos, verts[1].pos)));
    return 0;
}
