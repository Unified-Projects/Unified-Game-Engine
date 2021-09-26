#pragma once

//Includes
#include "Keyboard.h"
#include "Mouse.h"

namespace UnifiedEngine {
	class InputClass {
	private:
	public:
		//Public Input Types
		KeyClass Keyboard;
		MouseClass Mouse;
		
		//Initialse Others
		InputClass(GLFWwindow* window, ivec2* FrameBuffer)
			: Keyboard(window), Mouse(window, FrameBuffer)
		{

		}
	};
}
