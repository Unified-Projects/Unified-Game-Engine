#include <Unified-Engine/Objects/objectComponent.h>
#include <Unified-Engine/Objects/camera.h>
#include <Unified-Engine/Objects/gameObject.h>
#include <Unified-Engine/debug.h>
#include <GLM/glm.hpp>
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>
#include <GLM/mat4x4.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

using namespace UnifiedEngine;

ObjectComponent::ObjectComponent(ObjectComponent* _Parent, ObjectComponentType Type, bool Component = false)
    : type(Type)
{
    //Required to for all components (Even GameObjects, but may be set to null for game references)
    this->Parent = _Parent;

    if(this->Parent){
        if(Component){
            this->Parent->Components.push_back(this);
        }
        else{
            this->Parent->Children.push_back(this);
        }
    }
}

ObjectComponent::~ObjectComponent(){
    //TODO: Kill all children and remove them
}

int ObjectComponent::Update(){

    //Children
    this->UpdateC();

    return 0;
}

int ObjectComponent::Render(){

    //Children
    this->RenderC();
    
    return 0;
}

glm::mat4 CalculateChildTransformationMatrix(Transform newT, Transform oldT, Transform ChildT){
    //Intialiser
    glm::mat4 Matrix(1.f);

    glm::vec3 Rotation = ChildT.Rotation + (newT.Rotation - oldT.Rotation);

    //Translations
    //Matrix = translate(Matrix, transform.Position);
    Matrix = glm::translate(Matrix, newT.Position);
    Matrix = glm::rotate(Matrix, glm::radians(Rotation.x), glm::vec3(1.f, 0.f, 0.f));
    Matrix = glm::rotate(Matrix, glm::radians(Rotation.y), glm::vec3(0.f, 1.f, 0.f));
    Matrix = glm::rotate(Matrix, glm::radians(Rotation.z), glm::vec3(0.f, 0.f, 1.f));
    Matrix = glm::translate(Matrix, ChildT.Position - newT.Position);
    // Matrix = glm::scale(Matrix, ChildT.Scale);

    //Return
    return Matrix;
}

int ObjectComponent::CalcFollow(ObjectComponent* obj){
    // TODO: ROTATIONS
    switch (this->type)
    {
    case OBJECT_CAMERA_OBJECT:
        {
            Camera* parent = (Camera*)this;

            switch (obj->type)
            {
            case OBJECT_CAMERA_OBJECT:
                {
                    Camera* child = (Camera*)obj;

                    child->transform.Position += parent->transform.Position - parent->transformOld.Position;

                    // glm::mat4 Matrix = CalculateChildTransformationMatrix(parent->transform, parent->transformOld, child->transform);

                    // child->transform.Position = glm::vec3(glm::vec4(child->transform.Position, 1) * Matrix);
			        // child->transform.Rotation = glm::vec3(glm::vec4(child->transform.Rotation, 1) * Matrix);

                    return 0;
                }
            case OBJECT_GAME_OBJECT:
                {
                    GameObject* child = (GameObject*)obj;

                    child->transform.Position += parent->transform.Position - parent->transformOld.Position;

                    glm::mat4 Matrix = CalculateChildTransformationMatrix(parent->transform, parent->transformOld, child->transform);

                    child->transform.Position = glm::vec3(glm::vec4(child->transform.Position, 1) * Matrix);
			        child->transform.Rotation = glm::vec3(glm::vec4(child->transform.Rotation, 1) * Matrix);
                    return 0;
                }
            default:
                return -1;
            };
        }
    case OBJECT_GAME_OBJECT:
        {
            GameObject* parent = (GameObject*)this;

            switch (obj->type)
            {
            case OBJECT_CAMERA_OBJECT:
                {
                    Camera* child = (Camera*)obj;

                    child->transform.Position += parent->transform.Position - parent->transformOld.Position;

                    // glm::mat4 Matrix = CalculateChildTransformationMatrix(parent->transform, parent->transformOld, child->transform);

                    // child->transform.Position = glm::vec3(glm::vec4(child->transform.Position, 1) * Matrix);
			        // child->transform.Rotation = glm::vec3(glm::vec4(child->transform.Rotation, 1) * Matrix);
                    return 0;
                }
            case OBJECT_GAME_OBJECT:
                {
                    GameObject* child = (GameObject*)obj;

                    child->transform.Position += parent->transform.Position - parent->transformOld.Position;

                    // glm::mat4 Matrix = CalculateChildTransformationMatrix(parent->transform, parent->transformOld, child->transform);

                    // child->transform.Position = glm::vec3(glm::vec4(child->transform.Position, 1) * Matrix);
			        // child->transform.Rotation = glm::vec3(glm::vec4(child->transform.Rotation, 1) * Matrix);
                    return 0;
                }
            default:
                return -1;
            };
        }
    default:
        return -1;
    };
}

int ObjectComponent::UpdateC(){
    for (auto i = this->Components.begin(); i != this->Components.end(); i++) {
        (*i)->Update();
    }
    for (auto i = this->Children.begin(); i != this->Children.end(); i++) {
        CalcFollow((*i));
        (*i)->Update();
    }

    return 0;
}

int ObjectComponent::RenderC(){
    for (auto i = this->Components.begin(); i != this->Components.end(); i++) {
        (*i)->Render();
    }
    for (auto i = this->Children.begin(); i != this->Children.end(); i++) {
        (*i)->Render();
    }
    
    return 0;
}

ObjectComponent* ObjectComponent::GetCompoentOfType(ObjectComponentType type){
    ObjectComponent* ReturnPoint = nullptr;

    for(auto i = this->Components.begin(); i != this->Components.end(); i++){
        if((*i)->type == type){
            ReturnPoint = *i;
            break;
        }
    }

    return ReturnPoint;
}

std::list<ObjectComponent*> ObjectComponent::GetCompoentsOfType(ObjectComponentType type){
    std::list<ObjectComponent*> ReturnPoint = {};
    
    for(auto i = this->Components.begin(); i != this->Components.end(); i++){
        if((*i)->type == type){
            ReturnPoint.push_back(*i);
        }
    }

    return ReturnPoint;
}

ObjectComponent* ObjectComponent::GetChildOfType(ObjectComponentType type){
    ObjectComponent* ReturnPoint = nullptr;

    for(auto i = this->Children.begin(); i != this->Children.end(); i++){
        if((*i)->type == type){
            ReturnPoint = *i;
            break;
        }
    }

    return ReturnPoint;
}

std::list<ObjectComponent*> ObjectComponent::GetChildrenOfType(ObjectComponentType type){
    std::list<ObjectComponent*> ReturnPoint = {};
    
    for(auto i = this->Children.begin(); i != this->Children.end(); i++){
        if((*i)->type == type){
            ReturnPoint.push_back(*i);
        }
    }

    return ReturnPoint;
}