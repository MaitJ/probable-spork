#include <stdlib.h>
#include "window.hpp"
#include <iostream>
#include <event_handler.hpp>

void GameWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        std::cout << "A pressed" << std::endl;
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
        EventHandler::emitEvent(Events::LIGHT_TOGGLE);
}

void GameWindow::error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

GameWindow::GameWindow() {
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
 
    this->window = glfwCreateWindow(1920, 1080, "Simple example", primary_monitor, NULL);
    if (!this->window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(this->window, key_callback);
 
    glfwMakeContextCurrent(this->window);
    gladLoadGL();
    glfwSwapInterval(1);
}
