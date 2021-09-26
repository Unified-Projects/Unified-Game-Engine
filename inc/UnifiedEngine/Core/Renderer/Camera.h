#pragma once

//Includes
#include "./RenderInfo.h"
#include "../Game/GlobalSettings.h"

namespace UnifiedEngine {
	class Camera {
	private:
		//Private
		vec3 worldUp;

		vec3 ViewUp;
		vec3 ViewRight;

	public:
		//Perspective Matrix
		float FOV;
		float FarPlane;
		float NearPlane;

		//Angles
		vec3 ViewFront;

		vec3 up;
		vec3 front;
		vec3 right;

		//Position
		Transform transform;

		//Initialise Defaults
		Camera() {
			this->FOV = 90.f;
			this->FarPlane = 1000.f;
			this->NearPlane = 0.01f;

			this->transform.Position = vec3(0, 0, 0);
			this->transform.Rotation = vec3(0, -90, 0);

			this->worldUp = vec3(0, 1, 0);

			this->up = this->worldUp;
			this->front = vec3(0);
			this->right = vec3(0);

			this->ViewFront = vec3(0.f);
			this->ViewRight = vec3(0.f);
			this->ViewUp = vec3(0.f);
		}

		//Change Angles
		void Update() {
			//Game Type
			if (Game_2D) {
				//Calculate Solid
				this->ViewFront.x = cos(radians(-90.f)) * cos(radians(0.f));
				this->ViewFront.y = sin(radians(0.f));
				this->ViewFront.z = sin(radians(-90.f)) * cos(radians(0.f));
			}
			else {
				//Calculate Dynamic
				this->ViewFront.x = cos(radians(this->transform.Rotation.y)) * cos(radians(this->transform.Rotation.x));
				this->ViewFront.y = sin(radians(this->transform.Rotation.x));
				this->ViewFront.z = sin(radians(this->transform.Rotation.y)) * cos(radians(this->transform.Rotation.x));
			}

			//Assigning
			this->ViewFront = normalize(this->ViewFront);

			this->ViewRight = normalize(cross(this->ViewFront, this->worldUp));
			this->ViewUp = normalize(cross(this->ViewRight, this->ViewFront));

			this->front.x = cos(radians(this->transform.Rotation.y)) * cos(radians(this->transform.Rotation.x));
			this->front.y = this->front.y;
			this->front.z = sin(radians(this->transform.Rotation.y)) * cos(radians(this->transform.Rotation.x));

			this->front = normalize(this->front);

			this->right = normalize(cross(this->front, this->worldUp));
			this->up = normalize(cross(this->right, this->front));

			//Matrixes
			CamMatrix = CalculateViewMatrix(this->transform, this->ViewFront, this->ViewUp);
			CamViewFront = this->ViewFront;
		}
	};
}