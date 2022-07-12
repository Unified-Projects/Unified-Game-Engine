#pragma once

#include <Unified-Engine/Core/GameInteractionObject.h>
#include <Unified-Engine/Core/Display/window.h>
#include <Unified-Engine/Core/config.h>
#include <Unified-Engine/includeGL.h>
#include <Unified-Engine/Objects/camera.h>
#include <Unified-Engine/Objects/objectComponent.h>
#include <Unified-Engine/Objects/Components/shaderObject.h>
#include <list>

namespace UnifiedEngine
{
    int __INIT__ENGINE();

    class GameInstance{
        friend GameInteractionObject;
        friend Window;
        friend Camera;
        friend ShaderObject;
    protected:
        //Interaction Points
        std::list<Window*> __windows = {};
        bool gladInited = false;

    public:
        Camera* camera = nullptr;
        glm::mat4 ProjectionMatrix = glm::mat4(1.f);

        std::list<ObjectComponent*> objects = {};

    protected:
        //Interaction Functions
        int _Init_Glad();

    public:
        //Constructors
        GameInstance();
        ~GameInstance();

    public:
        //Ticking
        int Update();
        int Render();
    };

    extern GameInstance* __GAME__GLOBAL__INSTANCE__;
} // namespace UnifiedEngine
