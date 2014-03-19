//
//  main.c
//  Hyperbolic_C
//
//  Created by Lito Nicolai on 2/6/14.
//  Copyright (c) 2014 Lito Nicolai. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "mesh_elements.h"
#include "verlet.h"
#include "draw.h"

// TODO: refactor OpenGL into a separate file

unsigned char pause = 0;
unsigned char fixpt_on = 0;
unsigned char gravity_on = 0;

int main(int argc, const char * argv[])
{
    int NUM_PARTICLES;
    int NUM_EDGES;
    
    // Open verts file
    FILE *fv;
    fv = fopen("../data/verts", "r+");

    if( fv == NULL){
        printf("Cannot find file ../data/verts\n");
        exit(-1);
    }

    // Get the number of verts
    fscanf(fv, "%d", &NUM_PARTICLES);

    // Allocate the particle-array
    Particle* p = (Particle *) calloc(NUM_PARTICLES,
            sizeof(Particle[NUM_PARTICLES]));

    // Loop through the vert file to
    // fill the particle-array
    for (int i = 0; i < NUM_PARTICLES; i++){
        fscanf(fv, "%lf %lf %lf" 
                  "%lf %lf %lf", 
                &p[i].pos.x, &p[i].pos.y, &p[i].pos.z,
                &p[i].prev_pos.x, &p[i].prev_pos.y, &p[i].prev_pos.z);

        if (i == 0 && fixpt_on){
            p[i].invmass = 0.f;
        }
        else {
            p[i].invmass = 1.f;
        }
    }


    fclose(fv);
    
    // Open edges file
    FILE *fe;
    fe = fopen("../data/edges", "r+");

    if (fe == NULL){
        printf("Cannot find file ../data/edges\n");
        return -1;
    }

    // Get the number of edges
    fscanf(fe, "%d", &NUM_EDGES);

    // Allocate the edge-array
    Edge* e = (Edge *) calloc(NUM_EDGES,
            sizeof(Edge[NUM_EDGES]));

    // Loop through the file to fill the 
    // edge-array
    for (int i = 0; i < NUM_EDGES; i++){
        fscanf(fe, "%d %d %lf",
                &e[i].a, &e[i].b, &e[i].length);
    }

    printf("%d\n",NUM_EDGES);
    fclose(fv);


/* ----------------------------------------------*/


    // OPENGL 
    


    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()){
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 960, "Jellyfish Tentacles", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // Jitter once
    jitter_x(p, 0.01, NUM_PARTICLES);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        draw(window);

        glBegin(GL_LINES);
        for (int i = 0; i < NUM_EDGES; ++i){

            vector v1 = p[e[i].a].pos;
            vector v2 = p[e[i].b].pos;
            glColor3f(1.0, 1.0/v_magnitude(v_sub(v1, v2)), 0.0);

            glVertex3f(v1.x, v1.y, v1.z);
            glVertex3f(v2.x, v2.y, v2.z);
        }
        glEnd();

        // run the Verlet functions
        if (!pause) {

            if (gravity_on){
                    apply_gravity(p, NUM_PARTICLES);
            }

            integrate_momentum(p, NUM_PARTICLES, deltaTime);
            satisfy_constraints(p, e, NUM_EDGES, 1.0);
            resolve_collision(p, e, NUM_PARTICLES);
        }

/*
        glBegin(GL_POINTS);
        glColor3f( 0.95, 0.207, 0.031);
        for (int i = 0; i < NUM_PARTICLES; ++i){
            vector v = p[i].pos;
            glVertex3f(v.x, v.y, v.z);
        }
        glEnd();
*/
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

