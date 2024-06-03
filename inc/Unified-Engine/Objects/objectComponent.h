#pragma once

#include <list>
#include <Unified-Engine/Objects/Components/transform.h>
#include <GLM/vec3.hpp>

namespace UnifiedEngine
{
    enum ObjectComponentType{
        OBJECT_GAME_OBJECT = 0,
        OBJECT_SHADER_OBJECT,
        OBJECT_CAMERA_OBJECT,
        OBJECT_SCRIPTABLE_OBJECT,
        OBJECT_SKYBOX,
        OBJECT_MATERIAL,
        OBJECT_RIGID_BODY,
        OBJECT_COLLIDER,
    };

    class ObjectComponent{
    protected:
		glm::vec3 worldUp;
    public:
        ObjectComponent* Parent = nullptr;
        std::list<ObjectComponent*> Children = {};
        std::list<ObjectComponent*> Components = {};
        Transform transform = {};
        bool Enabled = true;
    public:
        const ObjectComponentType type;

        ObjectComponent(ObjectComponent* _Parent, ObjectComponentType Type, bool Component = false);
        ~ObjectComponent();

    public:
        int UpdateC(); //Chilren
        virtual int Update();
        int RenderC(); //Children
        virtual int Render();

    public:
        ObjectComponent* GetCompoentOfType(ObjectComponentType type);
        std::list<ObjectComponent*> GetCompoentsOfType(ObjectComponentType type);
        ObjectComponent* GetChildOfType(ObjectComponentType type);
        std::list<ObjectComponent*> GetChildrenOfType(ObjectComponentType type);
    
    protected:
        int CalcFollow(ObjectComponent* obj);

        void* Main;
    };
} // namespace UnifiedEngine
