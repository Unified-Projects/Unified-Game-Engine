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
    void NormalizeQuaternion(glm::quat &Quaternion) {
        float mag = std::sqrt(Quaternion.w * Quaternion.w + Quaternion.x * Quaternion.x + Quaternion.y * Quaternion.y + Quaternion.z * Quaternion.z);
        Quaternion /= mag;
    }
}