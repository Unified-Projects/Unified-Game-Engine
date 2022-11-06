#pragma once

#include <Unified-Engine/includeGL.h>
#include <GLM/vec2.hpp>

namespace UnifiedEngine
{
    enum MouseButtonEnums{
        //Main
		Mouse_LEFT = GLFW_MOUSE_BUTTON_LEFT,
		Mouse_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
		Mouse_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,

		//Extra
		Mouse_1 = GLFW_MOUSE_BUTTON_1,
		Mouse_2 = GLFW_MOUSE_BUTTON_2,
		Mouse_3 = GLFW_MOUSE_BUTTON_3,
		Mouse_4 = GLFW_MOUSE_BUTTON_4,
		Mouse_5 = GLFW_MOUSE_BUTTON_5,
		Mouse_6 = GLFW_MOUSE_BUTTON_6,
		Mouse_7 = GLFW_MOUSE_BUTTON_7,
		Mouse_8 = GLFW_MOUSE_BUTTON_8,
    };
    
    class CursorController{
    private:
		//Window
		GLFWwindow* window;
	public:
		//Cusor Locing
		bool isLocked;

		//Intitalise
		CursorController(GLFWwindow* window);

		//Lock To Center
		void Locked();

		//Unlock
		void Free();
    };

    class MouseController{
    private:
		//Movement
		bool firstMouse;
		double mouseX;
		double mouseY;
		double lastMouseX;
		double lastMouseY;

		//Scroll
		double scrollX;
		double scrollY;

		//Window
		GLFWwindow* window;
		//Screen Size
		glm::ivec2 FB;

	public:

        CursorController Cursor;

		//Init
		MouseController(GLFWwindow* window, glm::ivec2 FB);

		//Buttons
		bool MousePressed(MouseButtonEnums key);

		//Get Position Depending on mode
		glm::vec2 GetPosition();

		//Return Positive or Negative Scroll
		int Scroll();

		//For Callback
		void setScroll(double x, double y);
    };
} // namespace UnifiedEngine
