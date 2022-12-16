#include "keyboard.hpp"
#include "entities/camera.hpp"
#include "../events/event_handler.hpp"

std::unordered_map<int, bool> Keyboard::key_states;

void Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_W){
        if (action != GLFW_RELEASE)
            Keyboard::key_states[GLFW_KEY_W] = true;
        else
            Keyboard::key_states[GLFW_KEY_W] = false;
    }
    if (key == GLFW_KEY_A){
        if (action != GLFW_RELEASE)
            Keyboard::key_states[GLFW_KEY_A] = true;
        else
            Keyboard::key_states[GLFW_KEY_A] = false;
    }
    if (key == GLFW_KEY_S){
        if (action != GLFW_RELEASE)
            Keyboard::key_states[GLFW_KEY_S] = true;
        else
            Keyboard::key_states[GLFW_KEY_S] = false;
    }
    if (key == GLFW_KEY_D){
        if (action != GLFW_RELEASE)
            Keyboard::key_states[GLFW_KEY_D] = true;
        else
            Keyboard::key_states[GLFW_KEY_D] = false;
    }

}
