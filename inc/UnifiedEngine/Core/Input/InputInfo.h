#pragma once

//Includes
#include "../OpenGL/OpenGLInc.h"

namespace UnifiedEngine {
	//Delay to one key
	int LastKeyPressed = -1;

	int LastCharecterPressed = -1;
	
	//Update last Pressed
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
			LastKeyPressed = key;
	}

	//Update Last Typable Key
	static void character_callback(GLFWwindow* window, unsigned int codepoint)
	{
		LastCharecterPressed = codepoint;
	}
}