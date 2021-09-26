#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef _OPENGLINFO
namespace UnifiedEngine {
	//Public Variables
	int GLMajor;
	int GLMinor;
}
#define _OPENGLINFO
#endif