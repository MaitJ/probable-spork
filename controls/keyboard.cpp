#include "keyboard.hpp"
#include "../entities/camera.hpp"
#include "../events/event_handler.hpp"

void Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        EventHandler::emitEvent<Direction>(Event<Direction>(EventType::MOVEMENT, Direction::FORWARD));
    }
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        EventHandler::emitEvent<Direction>(Event<Direction>(EventType::MOVEMENT, Direction::LEFT));
    }
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        EventHandler::emitEvent<Direction>(Event<Direction>(EventType::MOVEMENT, Direction::BACK));
    }
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        EventHandler::emitEvent<Direction>(Event<Direction>(EventType::MOVEMENT, Direction::RIGHT));
    }

}
