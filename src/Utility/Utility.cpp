#include <Unified-Engine/Utility/Utility.h>

namespace UnifiedEngine {

    /// @brief Normalizes euler angles between 0 and 360
    /// @param EulerAngle A 3d vector containing the euler angles
    void NormalizeAngles(glm::vec3 &EulerAngle) {
        EulerAngle.x -= (float)((int)std::ceil(EulerAngle.x) / 360) * 360.0;
        EulerAngle.y -= (float)((int)std::ceil(EulerAngle.y) / 360) * 360.0;
        EulerAngle.z -= (float)((int)std::ceil(EulerAngle.z) / 360) * 360.0;
        if (EulerAngle.x < 0) {
            EulerAngle.x += 360;
        }
        if (EulerAngle.y < 0) {
            EulerAngle.y += 360;
        }
        if (EulerAngle.z < 0) {
            EulerAngle.z += 360;
        }
    }
    /// @brief Normalizes the given quaternion
    /// @param Quaternion A quaternion
    void NormalizeQuaternion(glm::quat &Quaternion) {
        float mag = std::sqrt(Quaternion.w * Quaternion.w + Quaternion.x * Quaternion.x + Quaternion.y * Quaternion.y + Quaternion.z * Quaternion.z);
        Quaternion /= mag;
    }
    /// @brief Normalizes the given 3D vector
    /// @param Vector A 3D vector
    void Normalize3DVector(glm::vec3 &Vector) {
        float mag = std::sqrt(Vector.x * Vector.x + Vector.y * Vector.y + Vector.z * Vector.z);
        Vector = Vector / mag;
    }
    /// @brief Converts a polar quaternion to a normal quaterion
    /// @param Angle Angle of rotation in degrees
    /// @param Axis Axis of rotation
    /// @return A normalized quaternion
    glm::quat GetQuaternionFromPolar(float Angle, glm::vec3 Axis) {
        Angle /= 2;
        Angle -= (float)((int)std::ceil(Angle) / 360) * 360.0;
        if (Angle < 0) {
            Angle += 360;
        }
        Normalize3DVector(Axis);
        glm::quat quaternion = glm::quat(std::cos(glm::radians(Angle)), std::sin(glm::radians(Angle)) * Axis.x, std::sin(glm::radians(Angle)) * Axis.y, std::sin(glm::radians(Angle)) * Axis.z);
        NormalizeQuaternion(quaternion);
        return quaternion;
    }
    float GetMagnitude(glm::vec3 Vector) {
        return std::sqrt(Vector.x * Vector.x + Vector.y * Vector.y + Vector.z * Vector.z);
    }
}