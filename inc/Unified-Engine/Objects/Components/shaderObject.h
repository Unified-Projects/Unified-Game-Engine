#pragma once

#include <Unified-Engine/Core/Rendering/shader.h>
#include <Unified-Engine/Objects/objectComponent.h>
#include <Unified-Engine/Objects/Components/shaderArgument.h>
#include <list>

#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>
#include <GLM/mat3x3.hpp>
#include <GLM/mat4x4.hpp>

namespace UnifiedEngine
{
    class GameObject;

    class ShaderObject : public ObjectComponent{
    public:
        Shader* shader = nullptr;
        std::list<ShaderArguments> Arguments = {};

        bool Toggled = false;

    public:
        ShaderObject(Shader* shaderRef);
        ~ShaderObject();
    
    public:
        int Toggle();
        int PassArgs();
    };
} // namespace UnifiedEngine
