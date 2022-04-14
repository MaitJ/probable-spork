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
    if (key == GLFW_KEY_A && action == GLFW_PRESS){
        glm::mat4 cam_mov = glm::rotate(glm::mat4(1.0f), glm::radians(-10.f), glm::vec3(.0f, 1.f, .0f));
        EventHandler::emitEvent<glm::mat4>(Event<glm::mat4>(EventType::CAMERA_ORIENTATION,cam_mov));
    }
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
