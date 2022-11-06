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
    if(this->Parent->type != OBJECT_GAME_OBJECT){
        FAULT("Parent Not GameObject");
        return -1;
    }

    GameObject* parent = (GameObject*)this->Parent;

    //Gravity TODO:TODO: CONVERT THIS INTO A ROTATIONAL FORCE AS IT MAY BE HALF WAY OFFA BLOCK
    this->Velocity.y += this->Gravity * Time.DeltaTime;

    //Movement
    parent->transform.Position += this->Velocity * Time.DeltaTime * this->PositionLock;

    //Check Collitions

    //

    return 0;
}
int RigidBody::Render(){


    return 0;
}

int RigidBody::CheckIfCollided(Collider* collider1, Collider* collider2){


    return 0;
}