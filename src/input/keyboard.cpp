#include <Unified-Engine/input/keyboard.h>

using namespace UnifiedEngine;

//Assign Window
KeyboardController::KeyboardController(GLFWwindow* window) {
    this->window = window;
}

//check for key press
bool KeyboardController::KeyPressed(KeyboardButtonEnums key) {
    return (glfwGetKey(this->window, key) == GLFW_PRESS);
}

int Keys::LastKeyPressed = -1;
int Keys::LastCharecterPressed = -1;