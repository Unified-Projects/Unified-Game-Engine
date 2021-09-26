#pragma once

//Includes
#include "./Components/Parent.h"
#include "../Core/Renderer/RenderInfo.h"
#include "../Core/Game/GlobalSettings.h"

namespace UnifiedEngine {
	class GameObject {
	private:
		//Buffers
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;

		//Rotate Arround
		bool RotateArround = false;

		//Firtst Initiation
		bool VAOInit = false;

		//Buffer Inits
		void VAOInitiation() {
			//Clear Old
			if (this->VAO) {
				glDeleteBuffers(1, &this->VAO);
				glDeleteBuffers(1, &this->VBO);
				if (this->mesh.indices.size() > 0)
					glDeleteBuffers(1, &this->EBO);
			}

			//Generation
			glGenVertexArrays(1, &this->VAO);
			glBindVertexArray(this->VAO);

			glGenBuffers(1, &this->VBO);
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

			//Sort Out Data
			glBufferData(GL_ARRAY_BUFFER, this->mesh.vertices.size() * sizeof(Vertex), this->mesh.vertices.data(), GL_STATIC_DRAW);

			if (this->mesh.indices.size() > 0) {
				glGenBuffers(1, &this->EBO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

				glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->mesh.indices.size() * sizeof(GLuint), this->mesh.indices.data(), GL_STATIC_DRAW);
			}

			//Split Data
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
			glEnableVertexAttribArray(1);
			
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
			glEnableVertexAttribArray(2);
		
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
			glEnableVertexAttribArray(3);

			//Clear
			glBindVertexArray(0);

			//Init
			this->VAOInit = true;
		}

		//Sort Out 2D
		Transform GetTransformDimentionified() {
			//Remvoe Z
			Transform NewT = this->transform;
			vec3 pos(NewT.Position.x, NewT.Position.y, NewT.Position.z * !Game_2D);
			
			//Return
			NewT = Transform{pos, NewT.Rotation, NewT.Scale};
			return NewT;
		}

		//Shader Values
		void updateUniforms() {
			//Color And Ligting
			this->material.sendToShader(this->shader);

			//Matrices
			this->shader.setMat4fv(CalculateModelMatrix(this->GetTransformDimentionified(), this->transform.Position), "ModelMatrix");
			this->shader.setMat4fv(CamMatrix, "ViewMatrix");
			this->shader.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

			//Camera
			this->shader.setVec3f(CamViewFront, "cameraView");
			this->shader.setVec3f(CamPos, "cameraPos");
		}

	public:
		//Main
		Transform transform;
		Mesh mesh;
		Shader shader;

		bool Active;

		//Locators
		const char* Name;
		const char* Tag;

		//Display Colors and lighting
		Material material;

		//Init with default shaders and values
		GameObject()
			: shader("./rsc/DefaultShaders/Objects/vertex_core.glsl", "./rsc/DefaultShaders/Objects/fragment_core.glsl")
		{
			this->mesh = {};
			this->VAOInit = false;
			this->Active = true;
			this->Name = "";
			this->Tag = "";
		}

		//Delete Buffers on deconstruction
		~GameObject() {
			glDeleteBuffers(1, &this->VAO);
			glDeleteBuffers(1, &this->VBO);
			if (this->mesh.indices.size() > 0)
				glDeleteBuffers(1, &this->EBO);
		}

		//Use a separate origin for roation 
		void RotateArroundOrigin(vec3 Rotation, vec3 Origin) {
			//New Transform
			Transform transf;

			//Pre assign
			transf.Position = this->transform.Position;
			transf.Rotation = this->transform.Rotation + Rotation;
			transf.Scale = this->transform.Scale;
			
			//Matrix
			mat4 Matrix = CalculateModelMatrix(this->GetTransformDimentionified(), Origin);
			
			//Manipulate
			this->transform.Position = vec3(vec4(this->transform.Position, 1) * Matrix);
			this->transform.Rotation = vec3(vec4(this->transform.Rotation, 1) * Matrix);
		}

		//Update Models
		void Update() {
			
		}

		//Draw the object
		void Render() {
			if (this->Active) {
				//Shader Textures
				this->material.BindTextures();

				//Reinit VAO (Should Move To Update And Make Dynamic)
				if (!this->VAOInit) {
					this->VAOInitiation();
				}

				//Update Shader Values
				this->updateUniforms();
				
				//Load Shader
				this->shader.use();

				//Bind Buffers
				glBindVertexArray(this->VAO);
				
				//Use Method Based on Indicies or not
				if (this->mesh.indices.size() > 0)
					glDrawElements(GL_TRIANGLES, this->mesh.indices.size(), GL_UNSIGNED_INT, 0);
				else
					glDrawArrays(GL_TRIANGLES, 0, this->mesh.vertices.size());

				//Clearing
				glBindVertexArray(0);
				this->shader.unbind();
				this->material.UnBindTextures();
			}
		}
	};
}