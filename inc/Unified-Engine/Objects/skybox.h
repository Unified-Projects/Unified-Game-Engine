#pragma once

#include <Unified-Engine/Objects/objectComponent.h>
#include <GLM/vec3.hpp>

namespace UnifiedEngine
{
    class Skybox : public ObjectComponent{
    public:
        Skybox();
        ~Skybox();

    public:
        virtual int Update(){return 0;}
        virtual int Render(){return 0;}
    };

    class SkyboxSolidColor : public Skybox{
    public:
        glm::vec3 Color;

    public:
        SkyboxSolidColor(glm::vec3 Color);
        ~SkyboxSolidColor();
    
    public:
        int Update();
        int Render();
    };

    // TODO: THIS
    class SkyboxGradient : public Skybox{
    public:
        SkyboxGradient(){return;}
        ~SkyboxGradient(){return;}

    public:
        int Update(){return 0;}
        int Render(){return 0;}
    };

    // TODO: Textured Skybox
} // namespace UnifiedEngine
