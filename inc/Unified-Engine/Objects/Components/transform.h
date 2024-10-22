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
    class Transform{
    private:
		glm::vec3 _Rotation = glm::vec3(0.f); //!< Stores the rotation, in euler angles, of the current transform
        glm::quat _Quaternion = glm::quat(1.f, 0.f, 0.f, 0.f); //!< Stores the Quaternions of the current transform
        glm::vec3 _up; //!< Stores the up vector of the current transform
		glm::vec3 _front; //!< Stores the front vector of the current transform
		glm::vec3 _right;  //!< Stores the right vector of the current transform
    private:
        void CalculateNewDirectionVectors();
    public:
        glm::vec3 Position = glm::vec3(0.f); //!< Stores the position of the current transform
		glm::vec3 Scale = glm::vec3(1.f); //!< Stores the scale of the current transform
    public:
        void SetRotation(glm::quat rotation);
        void SetRotation(glm::vec3 rotation);
        void Rotate(glm::quat rotation);
        void Rotate(glm::vec3 rotation);
        void LookAt(glm::vec3 position);
        void SLerp(glm::vec3 position, float stepsize);
        void Move(glm::vec3 movement);
    public:
        glm::vec3& Rotation();
        glm::quat& Quaternion();
        glm::vec3& up();
        glm::vec3& front();
        glm::vec3& right();
    };
} // namespace UnifiedEngine
