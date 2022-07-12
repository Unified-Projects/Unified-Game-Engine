#pragma once

#include <Unified-Engine/Objects/objectComponent.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

namespace UnifiedEngine
{
    class Camera : public ObjectComponent{
    public:
        glm::mat4 ViewMatrix;
        glm::mat4 ProjectionMatrix;

        glm::vec3 Position;
        glm::vec3 Rotation;

        //Perspective Matrix
		float FOV;
		float FarPlane;
		float NearPlane;

		//Angles
		glm::vec3 ViewFront;

		glm::vec3 up;
		glm::vec3 front;
		glm::vec3 right;

    public:
        Camera();
        ~Camera();

        int Update();
        int Render();

    protected:
		glm::vec3 worldUp;

		glm::vec3 ViewUp;
		glm::vec3 ViewRight;
    };
} // namespace UnifiedEngine
