#include <stdlib.h>
#include "window.hpp"
#include <iostream>
#include <event_handler.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "controls/keyboard.hpp"

void GameWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void GameWindow::error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

GameWindow::GameWindow(float window_width, float window_height) {
    glfwSetErrorCallback(error_callback);
 
    if (!glfwInit())
        exit(EXIT_FAILURE);

    GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary_monitor);
 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_SAMPLES, 4);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
 
    this->window = glfwCreateWindow(window_width, window_height, "probable-spork", nullptr, nullptr);
    if (!this->window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(this->window, Keyboard::key_callback);

    //Mouse input
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(this->window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    

    glfwSetCursorPosCallback(this->window, Mouse::movement_callback);
 
    glfwMakeContextCurrent(this->window);
    gladLoadGL();
    glfwSwapInterval(1);
}
