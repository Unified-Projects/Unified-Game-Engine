#include <Unified-Engine/input/input.h>

using namespace UnifiedEngine;

//Update last Pressed
static void UnifiedEngine::Keys::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        LastKeyPressed = key;
}

//Update Last Typable Key
static void UnifiedEngine::Keys::character_callback(GLFWwindow* window, unsigned int codepoint)
{
    LastCharecterPressed = codepoint;
}

InputClass::InputClass(Window* windowObj)
    : Mouse(windowObj->Context(), glm::ivec2(windowObj->Config().x, windowObj->Config().y)), Keyboard(windowObj->Context())
{
    this->WindowObject = windowObj;

    glfwSetScrollCallback(windowObj->Context(), scroll_callback);
    glfwSetKeyCallback(windowObj->Context(), Keys::key_callback);
    glfwSetCharCallback(windowObj->Context(), Keys::character_callback);
}
InputClass::~InputClass(){

}

InputClass* UnifiedEngine::InputPointer = nullptr;

static void UnifiedEngine::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(InputPointer){
	    InputPointer->Mouse.setScroll(xoffset, yoffset);
    }
}