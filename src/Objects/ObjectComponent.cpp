#include <Unified-Engine/Objects/objectComponent.h>

using namespace UnifiedEngine;

ObjectComponent::ObjectComponent(ObjectComponent* _Parent, ObjectComponentType Type)
    : type(Type)
{
    //Required to for all components (Even GameObjects, but may be set to null for game references)
    this->Parent = _Parent;
}

ObjectComponent::~ObjectComponent(){
    //TODO: Kill all children and remove them
}

int ObjectComponent::Update(){

    //TODO: Add all update specifics and send update signal to children

    return 0;
}

int ObjectComponent::Render(){

    //TODO: Add all rendering specifics and send rendering signal to children
    
    return 0;
}