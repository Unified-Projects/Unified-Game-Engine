#pragma once

#include <Unified-Engine/Objects/objectComponent.h>
#include <GLM/vec3.hpp>

namespace UnifiedEngine
{
    class Collider;

    class RigidBody : public ObjectComponent{
    public:
        //Movement
        //TODO: Rotation Locks and Movement Locks
        glm::vec3 PositionLock = glm::vec3(1.0);
        glm::vec3 RotationLock = glm::vec3(1.0);

        int Mass = 1;
        int Gravity = -9.8;
        int FrictionLevel = 0;

        glm::vec3 Velocity = glm::vec3(0.0);

        bool Friction = true;
        bool UseGravity = true;

    public:
        RigidBody(ObjectComponent* parent); //Ensure Seupt As Component Not Child
        ~RigidBody();

    public:
        int Update();
        int Render();

    protected:
        int CheckIfCollided(Collider* collider1, Collider* collider2);
    };
} // namespace UnifiedEngine
