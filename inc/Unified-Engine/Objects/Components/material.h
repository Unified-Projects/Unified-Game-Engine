#pragma once

#include <Unified-Engine/Objects/objectComponent.h>
#include <GLM/vec3.hpp>
#include <Unified-Engine/Objects/Components/texture2d.h>

namespace UnifiedEngine
{
    class Material : public ObjectComponent{
    public:
        Material(ObjectComponent* Parent);
        ~Material();
    
    public:
        virtual int Update();
        virtual int Render();
    };

    class ColorMaterial : public Material{ //TODO:
    public:
        ColorMaterial(ObjectComponent* Parent);
        ~ColorMaterial();
    
    public:
        int Update();
        int Render();
    };

    class GradientMaterial : public Material{ //TODO:
    public:
        GradientMaterial(ObjectComponent* Parent);
        ~GradientMaterial();
    
    public:
        int Update();
        int Render();
    };

    class Texture2DMaterial : public Material{ //TODO:
    public:
        Texture2DMaterial(ObjectComponent* Parent, Texture2D* texture);
        ~Texture2DMaterial();

    public:
        Texture2D* texture;
    
    public:
        int Update();
        int Render();
    };
} // namespace UnifiedEngine
