#pragma once

#include <GLM/vec3.hpp>
#include <GLM/gtc/quaternion.hpp>
#include <GLM/ext/quaternion_float.hpp>
#include <cmath>
namespace UnifiedEngine {
    void NormalizeAngles(glm::vec3 &EulerAngle);
    void NormalizeQuaternion(glm::quat &Quaternion);
    void Normalize3DVector(glm::vec3 &Vector);
    glm::quat GetQuaternionFromPolar(float Angle, glm::vec3 Axis);
    float GetMagnitude(glm::vec3 Vector);
}