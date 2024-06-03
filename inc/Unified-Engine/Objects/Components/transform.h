#pragma once

#include <GLM/vec3.hpp>
#include <GLM/geometric.hpp>
#include <GLM/gtc/quaternion.hpp>
#include <GLM/ext/quaternion_float.hpp>
#include <GLM/trigonometric.hpp>
#include <Unified-Engine/Utility/Utility.h>
#include <Unified-Engine/debug.h>
#include <string>

namespace UnifiedEngine
{
    /// @brief Stores Position, Rotation (in both euler and quaternions) and scale
    struct Transform{
        glm::vec3 Position = glm::vec3(0.f);
		glm::vec3 Rotation = glm::vec3(0.f);
		glm::vec3 Scale = glm::vec3(1.f);
        glm::quat Quaternion = glm::quat(1.f, 0.f, 0.f, 0.f);
        glm::vec3 up;
		glm::vec3 front;
		glm::vec3 right;
        void SetRotation(glm::quat rotation);
        void SetRotation(glm::vec3 rotation);
        void Rotate(glm::quat rotation);
        void Rotate(glm::vec3 rotation);
        void LookAt(glm::vec3 position);
        void CalculateNewDirectionVectors();
    };
} // namespace UnifiedEngine
