#include <Unified-Engine/Objects/Components/rigidbody.h>
#include <Unified-Engine/Objects/Components/collider.h>
#include <Unified-Engine/Objects/gameObject.h>
#include <Unified-Engine/debug.h>
#include <Unified-Engine/Core/time.h>

using namespace UnifiedEngine;

RigidBody::RigidBody(ObjectComponent* parent)
    : ObjectComponent(parent, OBJECT_RIGID_BODY, true)
{

}
RigidBody::~RigidBody(){

}

int RigidBody::Update(){
    if (this->Parent->type != OBJECT_GAME_OBJECT) {
        FAULT("Parent Not GameObject");
        return -1;
    }

    GameObject* parent = (GameObject*)this->Parent;

    // Calculate adjusted acceleration with gravity applied (if enabled)
    glm::vec3 gravityForce = glm::vec3(0, Gravity * UseGravity * 10, 0);
    glm::vec3 AdjustedAcceleration = this->Acceleration + gravityForce;

    // Update velocity based on acceleration and time step
    this->Velocity += AdjustedAcceleration * Time.DeltaTime;

    // Apply drag to the velocity
    if (glm::length(this->Velocity) > 0.0f) {
        glm::vec3 dragForce = glm::normalize(this->Velocity) * glm::length(this->Velocity) * this->DragFactor;
        this->Velocity -= dragForce * Time.DeltaTime;
    }

    // Update the position of the parent object based on velocity and position lock
    parent->transform.Position += this->Velocity * Time.DeltaTime * this->PositionLock;

    // Reset acceleration for the next frame (forces should re-apply each frame)
    this->Acceleration = glm::vec3(0.0);

    return 0;
}
int RigidBody::Render(){


    return 0;
}

int RigidBody::CheckIfCollided(Collider* collider1, Collider* collider2){


    return 0;
}