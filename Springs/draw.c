// OpenGL functions that direct drawing and 
// camera controls

#include "draw.h"
#include "vectormath.h"
#include <math.h>
#include <stdio.h>

float zoom = 2.0;
float speed = 15.0;
float mouseSpeed = 0.5;

vector position = {0.0, 0.0, 0.0}; // Camera position
vector right; // Camera right vector
vector direction = {1.0, 0.0, 0.0}; // Camera is pointing towards
vector up = {0.0, 1.0, 0.0}; // Camera upvector

float FoV = 45.f; // Field of View

int width, height;
double xpos, ypos = 0.0;
float ratio;

float azimuth = 0.0;
float inclination = M_PI/2.0;


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

        // printf("%f %f %d %d\n", xpos, ypos, width, height);

        // Camera controls:
        azimuth += mouseSpeed * deltaTime *  ((float) width/2.f - xpos);
        inclination += mouseSpeed * deltaTime * ((float) height/2.f - ypos);
        
        // printf("%f\n", (width/2.f - (float) xpos));
        // printf("%f\n", (height/2.f - (float) ypos));
        // printf("%f\n", inclination);

        vector direction = { // Where we're looking
            sin(inclination) * cos(azimuth),
            cos(azimuth),
            sin(inclination) * sin(azimuth)
        };

        vector right = {
            sin(inclination) * cos(azimuth + M_PI/2.0),
            0.0,
            sin(inclination) * sin(azimuth + M_PI/2.0)
        };


        // vector up = v_cross(right, direction);

        // printf("%f %f %f\n", direction.x, direction.y, direction.z);
        // printf("%f\n", v_dot(direction, up));
        
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
        // Strafe down
        if (glfwGetKey(window, GLFW_KEY_SPACE ) == GLFW_PRESS){
            position = v_add(position, v_scalar_mul(up, (deltaTime * speed)));
        }
        // Strafe up
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS){
            position = v_sub(position, v_scalar_mul(up, (deltaTime * speed)));
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
                position.x + direction.x, position.y + direction.y, position.z + direction.z, 
                up.x, up.y, up.z
            );
        

        glfwSetCursorPos(window, width/2, height/2);
}
