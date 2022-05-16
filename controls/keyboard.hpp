#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../window.hpp"
#include <unordered_map>


class Keyboard {

public:
    static std::unordered_map<int, bool> key_states;
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif
