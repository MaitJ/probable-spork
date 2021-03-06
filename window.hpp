#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../controls/mouse.hpp"

class GameWindow {
public:
    GLFWwindow* window;
public:
    GameWindow(float window_width, float window_height);
private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void error_callback(int error, const char* description);
    static void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);
};

#endif
