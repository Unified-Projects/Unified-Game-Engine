#pragma once

#include <Unified-Engine/includeGL.h>
#include <vector>
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>

namespace UnifiedEngine
{   
    //A point on the model
	struct Vertex
	{
		//Values for rendering
		glm::vec3 position = {0, 0, 0};
		glm::vec3 color = {1, 1, 1};
		glm::vec2 uv = {0, 0};
		glm::vec3 normal = {0, 0, 0};
	};

	//Main Body
	struct Mesh
	{
		//Shape
		std::vector<Vertex> vertices = {};
		std::vector<GLuint> indices = {};
	};
} // namespace UnifiedEngine
