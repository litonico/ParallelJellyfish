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
#include "verlet.c"


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, const char * argv[])
{
    int NUM_PARTICLES;
    int NUM_EDGES;
    
    // Open verts file
    FILE *fv;
    fv = fopen("../data/verts", "r+");

    if( fv == NULL){
        printf("No such file\n");
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
    }

    printf("Second vector coords: %f %f %f\n", 
            p[1].pos.x, p[1].pos.y, p[1].pos.z);

    fclose(fv);
    
    // Open edges file
    FILE *fe;
    fe = fopen("../data/edges", "r+");

    if( fe == NULL){
        printf("No such file\n");
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

    printf("Second edge info: %d %d %f",
                e[1].a, e[1].b, e[1].length);

    fclose(fv);


/* ----------------------------------------------*/


    // OPENGL 

    
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */

    glfwSetKeyCallback(window, key_callback);
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        glPointSize(10.0);
        glBegin( GL_POINTS );
        glColor3f( 0.95f, 0.207, 0.031f );

        for (int i = 0; i < NUM_PARTICLES; i++){
            glVertex3f(p[i].pos.x, p[i].pos.y, p[i].pos.z);
        }

        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
    integrate_momentum(p, e, NUM_PARTICLES);
    satisfy_constraints(p, e, NUM_EDGES);
    resolve_collision(p,e, NUM_PARTICLES);
    return 0;
}

