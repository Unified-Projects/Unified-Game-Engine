#pragma once

//Includes
#include "./OpenGLInc.h"

//Namespace
namespace UnifiedEngine {

	//OpenGL Loading
	bool InititateOpenGL(){
		//Check Init
		if (!glfwInit()) {
			throw("ERR:::INIT::OPENGL:GLFW_FAILED_TO_INITIALISE");
			return false;
		}
		return true;
	}

	//GLAD Loading
	bool InititateOpenGLAddons() {
		//Check Init
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw("ERR:::INIT::GLAD:GLAD_FAILED_TO_LOAD");
			return false;
		}
		return true;
	}
}