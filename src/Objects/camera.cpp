#include <Unified-Engine/Objects/camera.h>

#include <GLM/glm.hpp>
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>
#include <GLM/mat4x4.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include <algorithm>
#include <vector>
#include <map>
#include <string>

using namespace UnifiedEngine;

Camera::Camera()
    : ObjectComponent(nullptr, OBJECT_CAMERA_OBJECT)
{
    this->FOV = 90.f;
    this->FarPlane = 1000.f;
    this->NearPlane = 0.01f;

    this->Position = glm::vec3(0, 0, 0);
    this->Rotation = glm::vec3(0, -90, 0);

    this->worldUp = glm::vec3(0, 1, 0);

    this->up = this->worldUp;
    this->front = glm::vec3(0);
    this->right = glm::vec3(0);

    this->ViewFront = glm::vec3(0.f);
    this->ViewRight = glm::vec3(0.f);
    this->ViewUp = glm::vec3(0.f);
}

Camera::~Camera(){

}


int Camera::Update(){
    //Game Type
    if (/*Game2D*/ 1 == 0) {
        //Calculate Solid
        this->ViewFront.x = cos(glm::radians(-90.f)) * cos(glm::radians(0.f));
        this->ViewFront.y = sin(glm::radians(0.f));
        this->ViewFront.z = sin(glm::radians(-90.f)) * cos(glm::radians(0.f));
    }
    else {
        //Calculate Dynamic
        this->ViewFront.x = cos(glm::radians(this->Rotation.y)) * cos(glm::radians(this->Rotation.x));
        this->ViewFront.y = sin(glm::radians(this->Rotation.x));
        this->ViewFront.z = sin(glm::radians(this->Rotation.y)) * cos(glm::radians(this->Rotation.x));
    }

    //Assigning
    this->ViewFront = normalize(this->ViewFront);

    this->ViewRight = normalize(cross(this->ViewFront, this->worldUp));
    this->ViewUp = normalize(cross(this->ViewRight, this->ViewFront));

    this->front.x = cos(glm::radians(this->Rotation.y)) * cos(glm::radians(this->Rotation.x));
    this->front.y = this->front.y;
    this->front.z = sin(glm::radians(this->Rotation.y)) * cos(glm::radians(this->Rotation.x));

    this->front = normalize(this->front);

    this->right = normalize(cross(this->front, this->worldUp));
    this->up = normalize(cross(this->right, this->front));

    //Matrixes
    this->ViewMatrix = glm::mat4(1.f);
    this->ViewMatrix = lookAt(Position, Position + ViewFront, ViewUp);

    return 0;
}

int Camera::Render(){
    return 0;
}
