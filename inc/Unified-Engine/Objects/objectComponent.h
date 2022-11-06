#pragma once

#include <list>

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
    public:
        ObjectComponent* Parent = nullptr;
        std::list<ObjectComponent*> Children = {};
        std::list<ObjectComponent*> Components = {};

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
