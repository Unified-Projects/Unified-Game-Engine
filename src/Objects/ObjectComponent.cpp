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

glm::mat4 CalculationOriginRotation(Transform newT, Transform oldT, Transform ChildT, glm::vec3 RotationMultiplyer = glm::vec3(-1, -1, -1)){
    //Intialiser
    glm::mat4 Matrix(1.f);

    glm::vec3 Rotation = (newT.Rotation - oldT.Rotation);
    glm::vec3 Origin = newT.Position;

    //Translations
    Matrix = glm::translate(Matrix, Origin - ChildT.Position); // Child -> Origin
    Matrix = glm::rotate(Matrix, glm::radians(Rotation.x), glm::vec3(RotationMultiplyer.x, 0.f, 0.f));
    Matrix = glm::rotate(Matrix, glm::radians(Rotation.y), glm::vec3(0.f, RotationMultiplyer.y, 0.f));
    Matrix = glm::rotate(Matrix, glm::radians(Rotation.z), glm::vec3(0.f, 0.f, RotationMultiplyer.z));
    Matrix = glm::translate(Matrix, ChildT.Position - Origin); // Origin -> Chid

    //Return
    return Matrix;
}

static int Bufferer = 0;

glm::mat4 CalculationCameraOriginRotation(Transform newT, Transform oldT, Transform ChildT, int Parent /*TODO*/, glm::vec3 FrontNew, glm::vec3* PrevRotation){
    //Intialiser
    glm::mat4 Matrix(1.f);

    glm::vec3 Rotation = (newT.Rotation); //  - oldT.Rotation
    glm::vec3 Origin = newT.Position;

    // Convert the View Forward Normalised Values into 3 different angles (We know one already)
    glm::vec3 Adjusted(0.f);

    // Y axis (Easy)
    Adjusted.y = Rotation.y;

    // X and Z (Hard <= 89 degrees)
        // Z
        // float MultiplyerZ = (abs(FrontNew.x) + abs(FrontNew.z)) + (abs(FrontOld.x) + abs(FrontOld.z));
        // MultiplyerZ /= 2;
        // MultiplyerZ = ((abs(FrontNew.z) + abs(FrontOld.z)) / 2)/MultiplyerZ;

        // Adjusted.z = Rotation.x * MultiplyerZ;

        // // // X
        // float MultiplyerX = (abs(FrontNew.x) + abs(FrontNew.z)) + (abs(FrontOld.x) + abs(FrontOld.z));
        // MultiplyerX /= 2;
        // MultiplyerX = ((abs(FrontNew.x) + abs(FrontOld.x)) / 2)/MultiplyerX;

        // Adjusted.x = Rotation.x * MultiplyerX;

        float MultiplyerZ = (FrontNew.z)/((FrontNew.x) + (FrontNew.z));
        Adjusted.x = Rotation.x * MultiplyerZ;

        // // X
        float MultiplyerX = (FrontNew.x)/((FrontNew.x) + (FrontNew.z));
        Adjusted.z = Rotation.x * MultiplyerX;

        Adjusted.x = Rotation.x;
        Adjusted.z = 0;

        // Using Trig
        /*float X2 = FrontNew.x * FrontNew.x;
        float Y2 = FrontNew.y * FrontNew.y;
        float Z2 = FrontNew.z * FrontNew.z;
      
        Adjusted.x = glm::degrees(atan2(sqrt(Y2 + Z2), FrontNew.x));
        Adjusted.y = glm::degrees(atan2(sqrt(Z2 + X2), FrontNew.y));
        Adjusted.z = glm::degrees(atan2(sqrt(X2 + Y2), FrontNew.z));

        float VMagnitude = sqrt(X2 + Y2 + Z2);

        Adjusted.x = glm::degrees(acos(FrontNew.x/VMagnitude)) - 90;
        Adjusted.y = glm::degrees(acos(FrontNew.z/VMagnitude)) - 90;
        Adjusted.z = glm::degrees(acos(FrontNew.y/VMagnitude)) - 90;*/

        

        // float MultiplyerX = ((FrontNew.y + FrontOld.y) / 2);
        // float MultiplyerZ = 1 - ((FrontNew.y + FrontOld.y) / 2);

        // Adjusted.x = Rotation.x * MultiplyerX;
        // Adjusted.z = Rotation.x * MultiplyerZ;

    if (Bufferer > 500){
        Bufferer = 0;

        // Convert the View Forward Normalised Values into 3 different angles (We know one already)
        glm::vec3 Adjusted2(0.f);

        // Y axis (Easy)
        Adjusted2.y = newT.Rotation.y;

        // X and Z (Hard <= 89 degrees)
            // Z

        //    Adjusted2.z = newT.Rotation.x * MultiplyerZ;

            // X

        //    Adjusted2.x = newT.Rotation.x * MultiplyerX;

        LOG("Front: ", FrontNew.x, " ", FrontNew.y, " ", FrontNew.z);
        LOG("Previous: ", PrevRotation[0].x, " ", PrevRotation[0].y, " ", PrevRotation[0].z);
        LOG("Adjusted: ", Adjusted.x, " ", Adjusted.y, " ", Adjusted.z);
        LOG("Diff: ", Adjusted.x - PrevRotation[0].x, " ", Adjusted.y - PrevRotation[0].y, " ", Adjusted.z - PrevRotation[0].z);
    }
    else{
        Bufferer++;
    }

    if((PrevRotation[0].x == -0.43f) && (PrevRotation[0].y == 0.43f) && (PrevRotation[0].z == -0.43f)){
        PrevRotation[0] = Adjusted;
        return glm::mat4(1.f);
    }

    // // Roation Directions
    glm::vec3 RotationMultiplyer(-1.f, 1.f, -1.f);
    // if(abs((int)(Adjusted.y) % 360) > 180){
    //     RotationMultiplyer.x = 1;
    // }
    // else{
    //     RotationMultiplyer.x = -1;
    // }

    //Translations
    Matrix = glm::translate(Matrix, Origin - ChildT.Position); // Child -> Origin
    
    // First undo last rotation
    // Matrix = glm::rotate(Matrix, glm::radians(-PrevRotation[0].x), glm::vec3(RotationMultiplyer.x, 0.f, 0.f));
    // Matrix = glm::rotate(Matrix, glm::radians(-PrevRotation[0].y), glm::vec3(0.f, RotationMultiplyer.y, 0.f));
    // Matrix = glm::rotate(Matrix, glm::radians(-PrevRotation[0].z), glm::vec3(0.f, 0.f, RotationMultiplyer.z));

    // Then apply new
    Matrix = glm::rotate(Matrix, glm::radians(Adjusted.x-PrevRotation[0].x), glm::vec3(RotationMultiplyer.x, 0.f, 0.f));
    Matrix = glm::rotate(Matrix, glm::radians(Adjusted.y-PrevRotation[0].y), glm::vec3(0.f, RotationMultiplyer.y, 0.f));
    Matrix = glm::rotate(Matrix, glm::radians(Adjusted.z-PrevRotation[0].z), glm::vec3(0.f, 0.f, RotationMultiplyer.z));

    Matrix = glm::translate(Matrix, ChildT.Position - Origin); // Origin -> Chid

    PrevRotation[0] = Adjusted;

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

                    // Perfom moving and then rotate around the origin
                    child->transform.Position += parent->transform.Position - parent->transformOld.Position;

                    // Calculate the rotation matrix
                    glm::mat4 RotationMatrix = CalculationOriginRotation(parent->transform, parent->transformOld, child->transform);

                    // Change position through matrix
                    child->transform.Position = glm::vec3(glm::vec4(child->transform.Position, 1) * RotationMatrix);

                    // Apply rotation
                    glm::vec3 Rotation = (parent->transform.Rotation - parent->transformOld.Rotation); // Rotation Difference
                    child->transform.Rotation += Rotation;

                    return 0;
                }
            case OBJECT_GAME_OBJECT:
                {
                    GameObject* child = (GameObject*)obj;

                    // Perfom moving and then rotate around the origin
                    child->transform.Position += parent->transform.Position - parent->transformOld.Position;
                    
                    // Multipyer
                    glm::vec3 RotationMultiplyer = glm::vec3(-1, 1, -1);

                    // Camera Fixups for X and Z axis
                    // LOG(parent->transformOld.Rotation.x, " ", parent->transformOld.Rotation.y, " ", parent->transformOld.Rotation.z);
                    // LOG(parent->ViewRight.x, " ", parent->ViewRight.y, " ", parent->ViewRight.z);
                    // LOG(parent->front.x, " ", parent->front.y, " ", parent->front.z);
                    // LOG("END");

                    // LOG("ADJUSTED: ", AdjustedNew.x, " ", AdjustedNew.y, " ", AdjustedNew.z);
                    // LOG("ViewFront: ", ViewFront.x, " ", ViewFront.y, " ", ViewFront.z);

                    // Calculate the rotation matrix
                    glm::mat4 RotationMatrix = CalculationCameraOriginRotation(parent->transform, parent->transformOld, child->transform, true, parent->ViewFront, &parent->OldAdjustedRotation);

                    // Change position through matrix
                    child->transform.Position = glm::vec3(glm::vec4(child->transform.Position, 1) * RotationMatrix);

                    // Apply rotation
                    glm::vec3 Rotation = (parent->transform.Rotation - parent->transformOld.Rotation); // Rotation Difference
                    // child->transform.Rotation -= Rotation * RotationMultiplyer;

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

                    // Perfom moving and then rotate around the origin
                    child->transform.Position += parent->transform.Position - parent->transformOld.Position;

                    // Calculate the rotation matrix
                    glm::mat4 RotationMatrix = CalculationOriginRotation(parent->transform, parent->transformOld, child->transform);

                    // Change position through matrix
                    child->transform.Position = glm::vec3(glm::vec4(child->transform.Position, 1) * RotationMatrix);

                    // Apply rotation
                    glm::vec3 Rotation = (parent->transform.Rotation - parent->transformOld.Rotation); // Rotation Difference
                    child->transform.Rotation += Rotation;

                    return 0;
                }
            case OBJECT_GAME_OBJECT:
                {
                    GameObject* child = (GameObject*)obj;

                    // Perfom moving and then rotate around the origin
                    child->transform.Position += parent->transform.Position - parent->transformOld.Position;

                    // Calculate the rotation matrix
                    // 
                    glm::mat4 RotationMatrix = CalculationOriginRotation(parent->transform, parent->transformOld, child->transform);

                    // Change position through matrix
                    child->transform.Position = glm::vec3(glm::vec4(child->transform.Position, 1) * RotationMatrix);

                    // Apply rotation
                    glm::vec3 Rotation = (parent->transform.Rotation - parent->transformOld.Rotation); // Rotation Difference
                    child->transform.Rotation += Rotation;

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
