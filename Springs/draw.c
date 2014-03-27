#include "draw.h"
#include "vectormath.h"
#include <math.h>
#include <stdio.h>

float zoom = 2.f;
float speed = 6.f;
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

        // Mouse tracking for camera
        // glfwSetInputMode(window, GL_CURSOR_, GL_TRUE);
        glfwGetCursorPos(window, &xpos, &ypos);
        // Camera controls:
        
        // horizontalAngle += mouseSpeed * deltaTime * ((float) width/2.f - xpos);
        // verticalAngle += mouseSpeed * deltaTime * ((float) height/2.f - ypos);
        
        // printf("%f\n", horizontalAngle);
        // printf("%f\n", verticalAngle);

        vector direction = {
            cos(verticalAngle) * sin(horizontalAngle), 
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
        };

        vector right = {
            sin(horizontalAngle - 3.14/2.0),
            0.0,
            cos(horizontalAngle - 3.14/2.0)
        };


        vector up = v_cross(right, direction);

        // printf("%f %f %f\n", up.x, up.y, up.z);
        
        // Handle movement
        // Move forward
        if (glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS){
            position = v_add(position, v_scalar_mul(direction, (deltaTime * speed)));
        }
        // Move backward
        if (glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS){
            position = v_sub(position, v_scalar_mul(direction, (deltaTime * speed)));
        }
        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS){
            position = v_add(position, v_scalar_mul(right, (deltaTime * speed)));
        }
        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS){
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
        gluPerspective(FoV, ratio, 0.1f, 100);
        //
        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        gluLookAt( // look where the mouse is pointing
                position.x, position.y, position.z, 
                0.f, 0.f, 0.f,//position.x + direction.x, position.y + direction.y, position.z + direction.z, 
                up.x, up.y, up.z
            );
        

        // glfwSetCursorPos(window, width/2, height/2);
}
