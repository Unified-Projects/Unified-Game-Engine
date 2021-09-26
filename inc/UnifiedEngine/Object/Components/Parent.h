#pragma once

//Includes
#include "./Transforms.h"
#include "./Mesh.h"
#include "./Resources.h"

namespace UnifiedEngine {
	//Cary over specific required values from objects
	struct Parent
	{
		//Locators
		const char* Name;
		const char* Tag;

		//Object
		Mesh* mesh;
		Transform* transform;

		//Whether is rendered
		bool* Active;

		//Render stuff
		Material material;
	};
}