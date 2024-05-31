#pragma once

#include <string>

namespace UnifiedEngine
{
    enum ShaderArgType{
        SHADER_ARG_NULL = -1,
        SHADER_ARG_INT = 0,
        SHADER_ARG_FLOAT = 1,
        SHADER_ARG_VEC2 = 2,
        SHADER_ARG_VEC3 = 3,
        SHADER_ARG_VEC4 = 4,
        SHADER_ARG_MAT3 = 5,
        SHADER_ARG_MAT4 = 6
    };

    /**
     * @brief How to use: First Value is a pointer to the data that will be sent every update. 
     *                    Second is the type of the data (Vec2, Int, Mat4, Texture). 
     *                    Lastly, the string value of what variable/uniform it is to be sent within the shader
     * 
     */
    struct ShaderArguments{
        void* dataLoc = nullptr;
        ShaderArgType type =  SHADER_ARG_NULL;
        std::string name = "";
    };
} // namespace UnifiedEngine
