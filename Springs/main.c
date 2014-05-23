// Main
// Read in vertex, edge, and face data, allocate memory,
// create OpenGL context (through GLFW) and run the 
// simulations outlined in verlet.c
//
// Created by Lito Nicolai on 2/6/14.
// Copyright (c) 2014 Lito Nicolai. All rights reserved.
//
//
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include "mesh_elements.h"
#include "verlet.h"
#include "draw.h"
#include "vert_export.h"
#include "bending_stiffness.h"

unsigned char paused = 0;
unsigned char momentum = 1;
unsigned char fixpt_on = 0;
unsigned char gravity_on = 0;

// Coefficient of Stiffness– lower is less stiff. 
// Keeping it < 1 is recommended. 0.1 is PLENTY stiff.
// 0 is completely floppy.
double stiffness_mu = 0.01;

// A lower value means slower and finer-grained simulation.
float simulation_speed = 0.1;

double currentTime = 0.0;
double lastTime = 0.0;
double deltaTime;

int main(int argc, const char * argv[])
{
    
    int NUM_PARTICLES;
    int NUM_EDGES;
    int NUM_FACEPAIRS;
    
    // Open verts file
    FILE *fv;
    fv = fopen("data/verts", "r+");

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
            p[i].invmass = 0.0;
        }
        else {
            p[i].invmass = 1.0;
        }
    }


    fclose(fv);
    
    // Open edges file
    FILE *fe;
    fe = fopen("data/edges", "r+");

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

    fclose(fe);

    // Open facepairs file
    FILE *ffp;
    ffp = fopen("data/facepairs", "r+");

    if (ffp == NULL){
        printf("Cannot find file ../data/facepairs\n");
        return -1;
    }

    fscanf(ffp, "%d", &NUM_FACEPAIRS);

    printf("%d\n", NUM_FACEPAIRS);

    FacePair* fp = (FacePair *) calloc(NUM_FACEPAIRS,
            sizeof(FacePair[NUM_FACEPAIRS]));

    for (int i = 0; i < NUM_FACEPAIRS; i++){
        fscanf(ffp, "%d %d %d %d",
                &fp[i].C, &fp[i].D, &fp[i].A, &fp[i].B);
        // Important! First two verts in a facepair are 
        // the internal edge, CD.
    }

    fclose(ffp);
    
    // Allocate memory for stiffness constants
    StiffnessDataContainer* StiffnessConstants = 
        (StiffnessDataContainer*) malloc(sizeof(StiffnessDataContainer));

    precompute_stiffness(stiffness_mu, StiffnessConstants);

        
/* ----------------------------------------------*/


    // OPENGL 
    


    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()){
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Jellyfish Tentacles", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // Jitter once
    jitter_x(p, 0.5, NUM_PARTICLES);

    // Hide cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // TODO: FIX! 
        /*
        if (deltaTime < 0.0167){
            usleep((deltaTime - 0.0167)*1000000);
        }
        */

        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;

        draw(window, deltaTime);

        glBegin(GL_LINES);
        for (int i = 0; i < NUM_EDGES; ++i){

            vector v1 = p[e[i].a].pos;
            vector v2 = p[e[i].b].pos;
            glColor3f(1.0, 1.0/v_magnitude(v_sub(v1, v2)), 0.0);

            glVertex3f(v1.x, v1.y, v1.z);
            glVertex3f(v2.x, v2.y, v2.z);
        }
        glEnd();

        // TEST AXES
        
        glBegin(GL_LINES);
        for (int i = 0; i < 3; ++i){
            vector v1 = {1.0, 0.0, 0.0};
            if (i == 1){
                v1.x = 0.0;
                v1.y = 1.0;
                v1.z = 0.0;
            }
            if (i == 2){
                v1.x = 0.0;
                v1.y = 0.0;
                v1.z = 1.0;
            }

            glColor3f(v1.x, v1.y, v1.z);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(v1.x, v1.y, v1.z);
        }
        glEnd();

       

        // Sticky Keys for paused
        // glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

        // Check if pausedd
        if (glfwGetKey(window, GLFW_KEY_P ) == GLFW_PRESS){
            paused = ~paused;
        }

        // run the Verlet functions
        if (!paused) {

            if (gravity_on){
                    apply_gravity(p, NUM_PARTICLES, simulation_speed);
            }

            if (momentum){
                integrate_momentum(p, NUM_PARTICLES, deltaTime, simulation_speed);
            }
            runtime_stiffness(p, fp, NUM_FACEPAIRS, StiffnessConstants, simulation_speed);
            satisfy_constraints(p, e, NUM_EDGES, simulation_speed);
            resolve_collision(p, e, NUM_PARTICLES, simulation_speed);
        }

        lastTime = currentTime;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    // Save the current vertex positions
    write_verts(p, e, NUM_PARTICLES, NUM_EDGES);

    return 0;
}

