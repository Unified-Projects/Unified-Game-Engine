#pragma once

#include <Unified-Engine/Objects/Components/transform.h>

namespace UnifiedEngine
{
    /// @brief Sets the rotation using a quaternion
    /// @param rotation A quaternion
    void Transform::SetRotation(glm::quat rotation) {
        this->_Quaternion = rotation;
        NormalizeQuaternion(this->_Quaternion);
        this->_Rotation = glm::eulerAngles(this->_Quaternion);
        this->_Rotation.x = glm::degrees(this->_Rotation.x);
        this->_Rotation.y = glm::degrees(this->_Rotation.y);
        this->_Rotation.z = glm::degrees(this->_Rotation.z);
        CalculateNewDirectionVectors();
    }
    /// @brief Rotates the transform using euler angles
    /// @param rotation Euler angles in degrees
    void Transform::SetRotation(glm::vec3 rotation) {
        this->_Rotation = rotation;
        NormalizeAngles(this->_Rotation);
        this->_Quaternion = glm::quat(glm::vec3(glm::radians(this->_Rotation.x), glm::radians(this->_Rotation.y), glm::radians(this->_Rotation.z)));
        CalculateNewDirectionVectors();
    }
    /// @brief Rotates the transform using a quaternion
    /// @param rotation A quaternion
    void Transform::Rotate(glm::quat rotation) {
        NormalizeQuaternion(rotation);
        this->_Quaternion = rotation * this->_Quaternion; //* glm::inverse(rotation);
        NormalizeQuaternion(this->_Quaternion);
        this->_Rotation = glm::eulerAngles(this->_Quaternion);
        this->_Rotation.x = glm::degrees(this->_Rotation.x);
        this->_Rotation.y = glm::degrees(this->_Rotation.y);
        this->_Rotation.z = glm::degrees(this->_Rotation.z);
        CalculateNewDirectionVectors();
    }
    /// @brief Rotates the transform using euler angles
    /// @param rotation A vector made of euler angles in degrees
    void Transform::Rotate(glm::vec3 rotation) {
        this->_Rotation += rotation;
        NormalizeAngles(this->_Rotation);
        this->_Quaternion = glm::quat(glm::vec3(glm::radians(this->_Rotation.x), glm::radians(this->_Rotation.y), glm::radians(this->_Rotation.z)));
        NormalizeQuaternion(this->_Quaternion);
        CalculateNewDirectionVectors();
    }
    /// @brief Rotates the object so that it would look at the given position
    /// @param position The position to look at
    void Transform::LookAt(glm::vec3 position) {
        glm::vec3 relativevec = position - this->Position;
        glm::vec3 axis = glm::cross(this->_front, relativevec);
        Normalize3DVector(axis);
        float angle = glm::degrees(std::acos(glm::dot(this->_front, relativevec) / (GetMagnitude(this->_front) * GetMagnitude(relativevec))));
        if (angle != 0 && angle == angle) {
            Transform::Rotate(GetQuaternionFromPolar(angle, axis));
            CalculateNewDirectionVectors();
        }
    }
    /// @brief Rotates the object by the given step size so that it would rotate towards the given position
    /// @param position The position to look at
    /// @param stepsize The percentage of the rotation that should be completed on this step
    void Transform::SLerp(glm::vec3 position, float stepsize) {
        glm::vec3 relativevec = position - this->Position;
        glm::vec3 axis = glm::cross(this->_front, relativevec);
        Normalize3DVector(axis);
        float angle = glm::degrees(std::acos(glm::dot(this->_front, relativevec) / (GetMagnitude(this->_front) * GetMagnitude(relativevec)))) * stepsize;
        if (angle != 0 && angle == angle) {
            Transform::Rotate(GetQuaternionFromPolar(angle, axis));
            CalculateNewDirectionVectors();
        }
    }
    /// @brief Moves the transform using the direction vectors
    /// @param movement How much of the right, up and front vectors the object will be moved by
    void Transform::Move(glm::vec3 movement) {
        glm::vec3 movementvec;
        movementvec += movement.x * this->_right;
        movementvec += movement.y * this->_up;
        movementvec += movement.z * this->_front;
        this->Position += movementvec;
    }
    /// @brief Updates the new direction vectors
    void Transform::CalculateNewDirectionVectors() {
        this->_front = this->_Quaternion * glm::vec3(0, 0, 1);
        this->_up = this->_Quaternion * glm::vec3(0, 1, 0);
        this->_right = this->_Quaternion * glm::vec3(-1, 0, 0);
    }
    /// @brief Gets the rotation of the transform.
    /// Returned values should not be edited, if edited they may cause errors in the program
    /// @return Rotation in euler angles
    glm::vec3& Transform::Rotation() {
        return this->_Rotation;
    }
    /// @brief Gets the rotation of the transform.
    /// Returned values should not be edited, if edited they may cause errors in the program
    /// @return Rotation in quaterions
    glm::quat& Transform::Quaternion() {
        return this->_Quaternion;
    }
    /// @brief Gets the up vector.
    /// Returned values should not be edited, if edited they may cause errors in the program
    /// @return Up vector
    glm::vec3& Transform::up() {
        return this->_up;
    }
    /// @brief Gets the front vector.
    /// Returned values should not be edited, if edited they may cause errors in the program
    /// @return Front vector
    glm::vec3& Transform::front() {
        return this->_front;
    }
    /// @brief Gets the right vector.
    /// Returned values should not be edited, if edited they may cause errors in the program
    /// @return Right vector
    glm::vec3& Transform::right() {
        return this->_right;
    }
} // namespace UnifiedEngine
