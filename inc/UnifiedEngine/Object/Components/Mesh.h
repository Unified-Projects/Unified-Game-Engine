#pragma once

//Includes
#include <vector>
#include "../../Maths/Maths.h"
#include "../../Core/OpenGL/OpenGLInc.h"

using namespace std;

namespace UnifiedEngine {
	//A point on the model
	struct Vertex
	{
		//Values for rendering
		vec3 position;
		vec3 color;
		vec2 uv;
		vec3 normal;
	};

	//Main Body
	struct Mesh
	{
		//Shape
		vector<Vertex> vertices;
		vector<GLuint> indices;
	};
}