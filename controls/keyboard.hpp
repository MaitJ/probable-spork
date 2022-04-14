#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GLFW/glfw3.h>

class Keyboard {
public:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif
