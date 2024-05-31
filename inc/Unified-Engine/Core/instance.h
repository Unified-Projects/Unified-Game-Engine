#pragma once

#include <Unified-Engine/Core/GameInteractionObject.h>
#include <Unified-Engine/Core/Display/window.h>
#include <Unified-Engine/Core/config.h>
#include <Unified-Engine/includeGL.h>
#include <Unified-Engine/Objects/camera.h>
#include <Unified-Engine/Objects/objectComponent.h>
#include <Unified-Engine/Objects/Components/shaderObject.h>
#include <list>
#include <Unified-Engine/input/input.h>
#include <Unified-Engine/Objects/skybox.h>
#include <Unified-Engine/Debug/Debugger.h>

namespace UnifiedEngine
{
    int __INIT__ENGINE();

    class GameInstance{
        friend GameInteractionObject;
        friend Window;
        friend Camera;
        friend ShaderObject;
        friend ObjectComponent;
        friend Debug::DebugWindow;
    private: //Rendering Stuff
        GLuint Framebuffer = 0;
        GLuint Renderbuffer = 0;
        GLuint Texture = 0;

    public:
        //Interaction Points
        std::list<Window*> __windows = {};
        bool gladInited = false;

        //Frames
        uint64_t FrameCounter = 0;
        float LastTime = 0;

    public:
        InputClass* Input = nullptr;
        Skybox* skybox = nullptr;
        glm::mat4 ProjectionMatrix = glm::mat4(1.f);

        std::list<ObjectComponent*> objects = {};

    public: // Debug stuff
        Debug::DebugWindow* debugWindow = nullptr;

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

    public: //Object Gathering
        ObjectComponent* GetObjectOfType(ObjectComponentType type);
        std::list<ObjectComponent*> GetObjectsOfType(ObjectComponentType type);
        GameObject* GetGameObjectWithName(std::string name);
        GameObject* GetGameObjectWithTag(std::string tag);
        std::list<GameObject*> GetGameObjectsWithName(std::string name);
        std::list<GameObject*> GetGameObjectsWithTag(std::string tag);
        Camera* GetMainCamera();

    private:
        int RecuseSearchChild(int Setting, bool multi, void* resultstore, std::list<ObjectComponent*>* StartingPoint, void* argument = nullptr);
    };

    extern GameInstance* __GAME__GLOBAL__INSTANCE__;

    int instantiate(ObjectComponent* Object);
    int destroy(ObjectComponent* Object);
} // namespace UnifiedEngine
