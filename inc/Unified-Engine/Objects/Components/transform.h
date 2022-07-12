#pragma once

#include <GLM/vec3.hpp>

namespace UnifiedEngine
{
    struct Transform{
        glm::vec3 Position = glm::vec3(0.f);
		glm::vec3 Rotation = glm::vec3(0.f);
		glm::vec3 Scale = glm::vec3(1.f);
    };
} // namespace UnifiedEngine
