#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GameWindow {
    static double prev_mouse_x, prev_mouse_y;
public:
    GLFWwindow* window;
public:
    GameWindow();
private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void error_callback(int error, const char* description);
    static void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);
};

#endif
