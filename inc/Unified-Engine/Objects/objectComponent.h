#pragma once

#include <vector>

namespace UnifiedEngine
{
    enum ObjectComponentType{
        OBJECT_GAME_OBJECT = 0,
        OBJECT_SHADER_OBJECT,
        OBJECT_CAMERA_OBJECT
    };

    class ObjectComponent{
    protected:
    public:
        ObjectComponent* Parent = nullptr;
        std::vector<ObjectComponent*> Children = {};

        bool Enabled = true;

        const ObjectComponentType type;

    public:
        ObjectComponent(ObjectComponent* _Parent, ObjectComponentType Type);
        ~ObjectComponent();

    public:
        virtual int Update();
        virtual int Render();
    
    protected:
        //TODO: To be called in Update and Render to update chilren and stuff
        int UpdateChilren();
        int RenderChildren();
    };
} // namespace UnifiedEngine
