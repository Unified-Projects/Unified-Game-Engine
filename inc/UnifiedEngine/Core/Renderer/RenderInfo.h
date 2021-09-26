#pragma once

//Includes
#include "../../Maths/Maths.h"

#ifndef _RENDERINFO
namespace UnifiedEngine {
	//Public Matrices and Positions
	mat4 CamMatrix;
	vec3 CamPos;
	mat4 ProjectionMatrix;
	mat4 UIProjection;
	vec3 CamViewFront;
}
#define _RENDERINFO
#endif