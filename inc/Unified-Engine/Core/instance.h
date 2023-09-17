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

namespace UnifiedEngine
{
    int __INIT__ENGINE();

    class GameInstance{
        friend GameInteractionObject;
        friend Window;
        friend Camera;
        friend ShaderObject;
        friend ObjectComponent;
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
        ObjectComponent* GameInstance::GetObjectOfType(ObjectComponentType type);
        std::list<ObjectComponent*> GameInstance::GetObjectsOfType(ObjectComponentType type);
        GameObject* GameInstance::GetGameObjectWithName(std::string name);
        GameObject* GameInstance::GetGameObjectWithTag(std::string tag);
        std::list<GameObject*> GameInstance::GetGameObjectsWithName(std::string name);
        std::list<GameObject*> GameInstance::GetGameObjectsWithTag(std::string tag);
        Camera* GameInstance::GetMainCamera();

    private:
        int GameInstance::RecuseSearchChild(int Setting, bool multi, void* resultstore, std::list<ObjectComponent*>* StartingPoint, void* argument = nullptr);
    };

    extern GameInstance* __GAME__GLOBAL__INSTANCE__;

    int instantiate(ObjectComponent* Object);
    int destroy(ObjectComponent* Object);
} // namespace UnifiedEngine
