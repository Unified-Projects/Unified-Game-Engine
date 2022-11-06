#include <Unified-Engine/input/mouse.h>
#include <Unified-Engine/debug.h>

using namespace UnifiedEngine;

//Init
MouseController::MouseController(GLFWwindow* window, glm::ivec2 FB)
    : Cursor(window)
{
    this->firstMouse = true;
    this->mouseX = 0;
    this->mouseY = 0;
    this->lastMouseX = 0;
    this->lastMouseY = 0;

    this->scrollX = 0;
    this->scrollY = 0;

    this->window = window;
    this->FB = FB;
}

//Buttons
bool MouseController::MousePressed(MouseButtonEnums key) {
    return (glfwGetMouseButton(this->window, key) == GLFW_PRESS);
}

//Get Position Depending on mode
glm::vec2 MouseController::GetPosition() {
    double x;
    double y;

    if (Cursor.isLocked) {
        glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

        //Calculate Change
        if (this->firstMouse)
        {
            this->lastMouseX = this->mouseX;
            this->lastMouseY = this->mouseY;
            this->firstMouse = false;
        }

        x = this->mouseX - this->lastMouseX;
        y = this->lastMouseY - this->mouseY;

        this->lastMouseX = this->mouseX;
        this->lastMouseY = this->mouseY;
    }
    else {
        //Get Position
        glfwGetCursorPos(this->window, &x, &y);

        glm::vec2 fb = this->FB;

        if (x > fb.x)
            x = fb.x;
        else if (x < 0)
            x = 0;

        if (y > fb.y)
            y = fb.y;
        else if (y < 0)
            y = 0;
    }

    return glm::vec2(x, y);
}

//Return Positive or Negative Scroll
int MouseController::Scroll() {
    int toReturn = 0;

    if (this->scrollY > 0){
        toReturn = 1;
    }
    else if (this->scrollY < 0){
        toReturn = -1;
    }
    else{
        toReturn = 0;
    }

    this->scrollX, this->scrollY = 0;

    return toReturn;
}

//For Callback
void MouseController::setScroll(double x, double y) {
    this->scrollX = x;
    this->scrollY = y;
}

//Intitalise
CursorController::CursorController(GLFWwindow* window) {
    this->isLocked = false;

    this->window = window;
}

//Lock To Center
void CursorController::Locked() {
    isLocked = true;
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

//Unlock
void CursorController::Free() {
    isLocked = false;
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}