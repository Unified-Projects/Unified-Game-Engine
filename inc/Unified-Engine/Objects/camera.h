#pragma once

#include <Unified-Engine/Objects/objectComponent.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <Unified-Engine/Objects/Components/transform.h>

namespace UnifiedEngine
{
    class Camera : public ObjectComponent{
      friend ObjectComponent;
    protected:
      Transform transformOld = {};
    public:
      glm::vec3 AdjustedRotation = {};
      glm::vec3 OldAdjustedRotation = glm::vec3(-0.43f, 0.43f, -0.43f);

    public:
        glm::mat4 ViewMatrix;
        glm::mat4 ProjectionMatrix;

        //Perspective Matrix
    float FOV;
    float FarPlane; //!< The far clipping plane
    float NearPlane; //!< The near clipping plane

    //Angles
    glm::vec3 ViewFront;

    public:
        Camera();
        ~Camera();

        int Update();
        int Render();

        glm::vec3 GetWorldUp() {return this->worldUp;}
        glm::vec3 GetViewRight() {return this->ViewRight;}

    protected:
    glm::vec3 worldUp;

    glm::vec3 ViewUp;
    glm::vec3 ViewRight;
    };
} // namespace UnifiedEngine
