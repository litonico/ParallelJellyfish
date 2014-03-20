#include "draw.h"
#include "vectormath.h"
#include <math.h>
#include <stdio.h>

float zoom = 2.f;
float speed = 3.f;
float mouseSpeed = 0.5;

vector position = {0.0, 0.0, 0.0}; // Camera position
vector right; // Camera right vector
vector direction; // Camera is pointing towards
vector up; // Camera upvector

float FoV = 45.f; // Field of View

int width, height;
double xpos, ypos;
float ratio;

float horizontalAngle = 3.14f;
float verticalAngle = 0.f;


void key_callback(
        GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void draw(GLFWwindow* window, float deltaTime){

        // The camera needs to be independent of the
        // view ratio of view window
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        //Mouse tracking for camera
        glfwGetCursorPos(window, &xpos, &ypos);
        // Camera controls:
        
        horizontalAngle += mouseSpeed * deltaTime * (width/2.f - xpos);
        verticalAngle += mouseSpeed * deltaTime * (height/2.f - ypos);
        
        printf("%f\n", horizontalAngle);
        printf("%f\n", verticalAngle);



        vector direction = {
            cos(verticalAngle) * sin(horizontalAngle), 
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
        };

        vector right = {
            sin(horizontalAngle - (3.14/2.0)),
            0.0,
            cos(horizontalAngle - (3.14/2.0))
        };

        vector up = v_cross(right, direction);


        // Handle movement
        // Move forward
        if (glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS){
            printf("up\n");
            position = v_add(position, v_scalar_mul(direction, (deltaTime * speed)));
            printf("%f %f %f\n", 
                position.x, position.y, position.z);
        }
        // Move backward
        if (glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS){
            position = v_sub(position, v_scalar_mul(direction, (deltaTime * speed)));
        }
        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
            position = v_add(position, v_scalar_mul(right, (deltaTime * speed)));
        }
        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS){
            position = v_sub(position, v_scalar_mul(right, (deltaTime * speed)));
        }

        // Initialize the viewport
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* CAMERA */

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity(); //Push identity matrix

        // glFrustum(.5, -.5, -.5 * ratio, .5 * ratio, 1, 50);
        // glOrtho(-ratio*10, ratio*10, -1.f*10, 1.f*10, 500.f, -500.f);
        gluPerspective(FoV, ratio, 0.1f, 50);
        //
        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        gluLookAt( // look where the mouse is pointing
                position.x, position.y, position.z, 
                position.x + direction.x, position.y + direction.y, position.z + direction.z, 
                up.x, up.y, up.z
            );
        

        glfwSetCursorPos(window, width/2, height/2);
}
