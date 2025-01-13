#pragma once

#include <Unified-Engine/includeGL.h>
#include <vector>
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <float.h>
#include <glm/common.hpp>

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

	// Helper struct for AABB (Axis-Aligned Bounding Box)
    struct AABB
    {
        glm::vec3 min;
        glm::vec3 max;

        AABB() : min(glm::vec3(FLT_MAX)), max(glm::vec3(-FLT_MAX)) {}

        inline void expand(const glm::vec3& point)
        {
            min = glm::min(min, point);
            max = glm::max(max, point);
        }

        inline bool intersects(const AABB* other) const
        {
            return (min.x <= other->max.x && max.x >= other->min.x) &&
                   (min.y <= other->max.y && max.y >= other->min.y) &&
                   (min.z <= other->max.z && max.z >= other->min.z);
        }
    };

	AABB* computeAABB(const class Mesh* mesh);

	//Main Body
	struct Mesh
	{
		//Shape
		std::vector<Vertex> vertices = {};
		std::vector<GLuint> indices = {};

		// AABB
		AABB* GeneratedAABB = nullptr;
	};
} // namespace UnifiedEngine
