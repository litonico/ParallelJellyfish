
void write_obj(Particle[] verts, Edge[] edges, 
        int num_particles, int num_edges){
    
    FILE *objfile;

    if (objfile == NULL){
        printf("No such file\n");
        return -1;
    }

    for (int i = 0; i < num_particles; i++){
        fprintf(objfile, "v %f %f %f\n", verts[i].pos.x
                verts[i].pos.y, verts[i].pos.z);
    }

    // Convert edges to faces
    // I don't know how to do this... 
    
    // Sort edges
    //
    
    for (int j = 0; j < num_edges; j++){
    }

}

