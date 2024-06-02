#pragma once

#include <Unified-Engine/Objects/Components/transform.h>

namespace UnifiedEngine
{
    /// @brief Sets the rotation using a quaternion
    /// @param rotation
    void Transform::SetRotation(glm::quat rotation) {
        this->Quaternion = rotation;
        this->Rotation = glm::eulerAngles(this->Quaternion);
        this->Rotation.x = glm::degrees(this->Rotation.x);
        this->Rotation.y = glm::degrees(this->Rotation.y);
        this->Rotation.z = glm::degrees(this->Rotation.z);
    }
    /// @brief Rotates the transform using euler angles
    /// @param rotation
    void Transform::SetRotation(glm::vec3 rotation) {
        this->Rotation = rotation;
        NormalizeAngles(this->Rotation);
        this->Quaternion = glm::quat(glm::vec3(glm::radians(this->Rotation.x), glm::radians(this->Rotation.y), glm::radians(this->Rotation.z)));
    }
    /// @brief Rotates the transform using a quaternion
    /// @param rotation
    void Transform::Rotate(glm::quat rotation) {
        NormalizeQuaternion(rotation);
        this->Quaternion = rotation * this->Quaternion;
        NormalizeQuaternion(this->Quaternion);
        this->Rotation = glm::eulerAngles(this->Quaternion);
        this->Rotation.x = glm::degrees(this->Rotation.x);
        this->Rotation.y = glm::degrees(this->Rotation.y);
        this->Rotation.z = glm::degrees(this->Rotation.z);
    }
    /// @brief Rotates the transform using euler angles
    /// @param rotation a glm::vec3 made of euler angles in degrees
    void Transform::Rotate(glm::vec3 rotation) {
        this->Rotation += rotation;
        NormalizeAngles(this->Rotation);
        this->Quaternion = glm::quat(glm::vec3(glm::radians(this->Rotation.x), glm::radians(this->Rotation.y), glm::radians(this->Rotation.z)));
        NormalizeQuaternion(this->Quaternion);
    }
} // namespace UnifiedEngine
