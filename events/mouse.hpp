#ifndef MOUSE_H
#define MOUSE_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Mouse {
    static float sensitivity;
    static glm::highp_vec2 prev_pos;

public:
    static void movement_callback(GLFWwindow* window, double xpos, double ypos);
};

#endif
