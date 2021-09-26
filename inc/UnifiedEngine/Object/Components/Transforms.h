#pragma once

//Includes
#include <GLM/vec3.hpp>

using namespace glm;

namespace UnifiedEngine {
	//For Screen Space
	struct Transform {
		vec3 Position = vec3(0.f);
		vec3 Rotation = vec3(0.f);
		vec3 Scale = vec3(1.f);
	};
}