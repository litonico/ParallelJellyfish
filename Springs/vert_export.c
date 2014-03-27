#include <stdio.h>
#include "vert_export.h"

void write_verts(Particle verts[], Edge edges[], 
        int num_particles, int num_edges){

    // Saves vertex positions to a file
    // that will be concatenated with 
    // /tmp/faces to form a valid .obj file.
    
    FILE *objfile;
    objfile = fopen("data/tmp/obj", "w+");

    if (objfile == NULL){
        printf("No such file data/tmp/obj!\n");
    }

    for (int i = 0; i < num_particles; i++){
        fprintf(objfile, "v %f %f %f \n", verts[i].pos.x, verts[i].pos.y, verts[i].pos.z);
    }

}

