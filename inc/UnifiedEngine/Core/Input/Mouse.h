#pragma once

//Includes
#include "../OpenGL/OpenGLInc.h"
#include "../../Maths/Maths.h"

namespace UnifiedEngine {
	enum MouseButtons {
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

	class CursorClass {
	private:
		//Window
		GLFWwindow* window;
	public:
		//Cusor Locing
		bool isLocked;

		//Intitalise
		CursorClass(GLFWwindow* window) {
			this->isLocked = false;

			this->window = window;
		}

		//Lock To Center
		void Locked() {
			isLocked = true;
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		//Unlock
		void Free() {
			isLocked = false;
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	};

	class MouseClass {
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
		ivec2* FB;

	public:
		//Cursor
		CursorClass Cursor;

		//Init
		MouseClass(GLFWwindow* window, ivec2* FB)
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
		bool MousePressed(MouseButtons key) {
			return (glfwGetMouseButton(this->window, key) == GLFW_PRESS);
		}	

		//Get Position Depending on mode
		vec2 GetPosition() {
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

				vec2 fb = *this->FB;

				if (x > fb.x)
					x = fb.x;
				else if (x < 0)
					x = 0;

				if (y > fb.y)
					y = fb.y;
				else if (y < 0)
					y = 0;
			}

			return vec2(x, y);
		}

		//Return Positive or Negative Scroll
		int Scroll() {
			int toReturn;

			if (this->scrollY > 0)
				toReturn = 1;
			else if (this->scrollY < 0)
				toReturn = -1;
			else
				toReturn = 0;

			this->scrollX, this->scrollY = 0;

			return toReturn;
		}

		//For Callback
		void setScroll(double x, double y) {
			this->scrollX = x;
			this->scrollY = y;
		}
	};
}