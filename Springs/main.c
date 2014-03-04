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

// TODO: refactor OpenGL and view controls
// into a separate file
GLfloat zoom = 2.f;
float currentTime;
float lastTime;
float deltaTime;
float position;
float speed = 3.f;
float mouseSpeed = 0.005;
float right;
float direction;


static void key_callback(
        GLFWwindow* window, int key, int scancode, int action, int mods) {

    // if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        // glfwSetWindowShouldClose(window, GL_TRUE);
    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        case GLFW_KEY_UP:
            zoom -= 0.25f;
            if (zoom < 0.f)
                zoom = 0.f;
            break;
        case GLFW_KEY_DOWN:
            zoom += 0.25f;
            break;
        case GLFW_KEY_A:
            position -= right * deltaTime * speed;
        case GLFW_KEY_D:
            position += right * deltaTime * speed;
        case GLFW_KEY_W:
            position += direction * deltaTime * speed;
        case GLFW_KEY_S:
            position += direction * deltaTime * speed;
        default:
            break;
    }
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
    

    float ratio;
    int width, height;
    double xpos, ypos;

    currentTime = glfwGetTime();

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()){
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // Jitter once
    jitter_x(p, 1.0, NUM_PARTICLES);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        deltaTime = currentTime - lastTime;


        // The camera needs to be independent of the
        // view ratio of view window
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        //Mouse tracking for camera
        glfwGetCursorPos(window, &xpos, &ypos);
        horizontalAngle += mouseSpeed * deltaTime * float(width/2.f - xpos );
        verticalAngle += mouseSpeed * deltaTime * float(height/2.f - ypos );
        
        // Initialize the viewport
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* CAMERA */

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity(); //Push identity matrix
        // glTranslatef(0, 0, -zoom); // Zoom controls: UP / DOWN

        // glFrustum(.5, -.5, -.5 * ratio, .5 * ratio, 1, 50);
        // glOrtho(-ratio, ratio, -1.f, 1.f, 500.f, -500.f);
        //
        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();
        // glTranslatef(0, 0, -zoom);

        glRotatef((float) glfwGetTime() * 50.f, 50.f, 50.f, 1.f);
        // glClearColor(0.0, 0.0, 0.0, 1.0);

        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        for (int i = 0; i < NUM_EDGES; ++i){
            vector v1 = p[e[i].a].pos;
            vector v2 = p[e[i].b].pos;
            glVertex3f(v1.x, v1.y, v1.z);
            glVertex3f(v2.x, v2.y, v2.z);
        }
        glEnd();

        lastTime = currentTime;
        // run the Verlet functions
        // integrate_momentum(p, e, NUM_PARTICLES);
        satisfy_constraints(p, e, NUM_EDGES);
        resolve_collision(p,e, NUM_PARTICLES);

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

