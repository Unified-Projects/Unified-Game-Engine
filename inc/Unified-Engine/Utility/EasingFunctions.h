#pragma once

#include <cmath>
namespace {
    #define PI 3.141593
}
namespace UnifiedEngine {
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseInSine(float x) {
        return 1 - std::cos(x * PI / 2);
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseOutSine(float x) {
        return std::sin(x * PI / 2);
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseInOutSine(float x) {
        return -(std::cos(x * PI) - 1) / 2;
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseInQuad(float x) {
        return x*x;
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseOutQuad(float x) {
        return 1-(1-x)*(1-x);
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseInOutQuad(float x) {
        return x < 0.5 ? 2 * x * x : 1 - std::pow(-2 * x + 2, 2) / 2;
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseInCubic(float x) {
        return x*x*x;
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseOutCubic(float x) {
        return 1-std::pow(1-x, 3);
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseInOutCubic(float x) {
        return x < 0.5 ? 4 * x * x * x : 1 - std::pow(-2 * x + 2, 3) / 2;
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseInQuartic(float x) {
        return x*x*x*x;
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseOutQuartic(float x) {
        return 1-std::pow(1-x, 4);
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseInOutQuartic(float x) {
        return x < 0.5 ? 8 * x * x * x * x : 1 - std::pow(-2 * x + 2, 4) / 2;
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseInQuintic(float x) {
        return x*x*x*x*x;
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseOutQuintic(float x) {
        return 1-std::pow(1-x, 5);
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseInOutQuintic(float x) {
        return x < 0.5 ? 16 * x * x * x * x * x : 1 - std::pow(-2 * x + 2, 5) / 2;
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseInExponential(float x) {
        return x == 0 ? 0 : std::pow(2, 10 * x - 10);
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseOutExponential(float x) {
        return x == 1 ? 1 : 1 - std::pow(2, -10 * x);
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseInOutExponential(float x) {
        return x == 0 ? 0 : x == 1 ? 1 : x < 0.5 ? std::pow(2, 20 * x - 10) / 2 : (2 - std::pow(2, -20 * x + 10)) / 2;
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseInCircle(float x) {
        return 1 - std::sqrt(1 - std::pow(x, 2));
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseOutCircle(float x) {
        return std::sqrt(1 - std::pow(x - 1, 2));
    }
    /// @brief Returns the eased value inputted
    /// @param x Value to be eased
    /// @return Eased value
    float EaseInOutCircle(float x) {
        return x < 0.5 ? (1 - std::sqrt(1 - std::pow(2 * x, 2))) / 2 : (std::sqrt(1 - std::pow(-2 * x + 2, 2)) + 1) / 2;
    }
}