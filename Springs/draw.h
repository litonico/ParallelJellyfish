
#ifndef draw_h
#define draw_h

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>


void draw(GLFWwindow* window, float deltaTime);

void key_callback(
        GLFWwindow* window, int key, int scancode, int action, int mods);

#endif
