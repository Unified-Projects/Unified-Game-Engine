#pragma once

//Includes
#include "../../Core/OpenGL/OpenGLInc.h"
#include "../../Maths/Maths.h"
#include "../../Core/Renderer/Shader.h"

#include <SOIL2/SOIL2.h>

namespace UnifiedEngine {
	int __NextAvailableTextureUnit = 1;

	class Texture2D {
	private:
		//Texture Reference to buffer
		GLuint id;

		//Image size
		int width;
		int height;

		//Unit to store texture when rendering
		GLint Unit;
	public:
		//Init from a file
		Texture2D(const char* fileLoc){
			//Get unit
			this->Unit = __NextAvailableTextureUnit;
			__NextAvailableTextureUnit++;

			//Check for a file location
			if(fileLoc != ""){
				//Read data
				unsigned char* image = SOIL_load_image(fileLoc, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

				//Create a texture
				glGenTextures(1, &this->id);
				glBindTexture(GL_TEXTURE_2D, this->id);

				//Configure
				//(Try Get Modifiable)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

				//If data exists write it
				if (image) {
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
					glGenerateMipmap(GL_TEXTURE_2D);
				}

				//Free memory
				glActiveTexture(0);
				glBindTexture(GL_TEXTURE_2D, 0);
				SOIL_free_image_data(image);
			}
		}

		//Use raw data for image
		Texture2D(unsigned char* Data, int imgWidth, int imgHeight){
			//Load texture unit
			this->Unit = __NextAvailableTextureUnit;
			__NextAvailableTextureUnit++;

			//Image settings
			this->width = imgWidth;
			this->height = imgHeight;

			//texture gen
			glGenTextures(1, &this->id);
			glBindTexture(GL_TEXTURE_2D, this->id);

			//Parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			//If data exists write it
			if (Data) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}

			//Free Texturs
			glActiveTexture(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		//No Loading
		Texture2D(){}
		
		//Deleting
		~Texture2D() {
			if(this->id)
				glDeleteTextures(1, &this->id);
		}

		//Get unit for referencing in shader
		GLint GetUnit() {
			return this->Unit;
		}

		//Binding
		void bind() {
			glActiveTexture(GL_TEXTURE0 + this->Unit);
			glBindTexture(GL_TEXTURE_2D, this->id);
		}

		//Unbinding
		void unbind() {
			glActiveTexture(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		//Update texture with a file
		void UpdateTexture(const char* fileLoc) {
			//Remove old
			if (this->id) {
				glDeleteTextures(1, &this->id);
			}

			//get data
			unsigned char* image = SOIL_load_image(fileLoc, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

			//Gen Texture
			glGenTextures(1, &this->id);
			glBindTexture(GL_TEXTURE_2D, this->id);

			//Parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			//Write data if exists
			if (image) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
				glGenerateMipmap(GL_TEXTURE_2D);

			}

			//Free memory
			glActiveTexture(0);
			glBindTexture(GL_TEXTURE_2D, 0);
			SOIL_free_image_data(image);
		}

		//Update File With Raw Data
		void UpdateTexture(unsigned char* Data, int imgWidth, int imgHeight) {
			//Remove old
			if (this->id) {
				glDeleteTextures(1, &this->id);
			}

			//Configures
			this->width = imgWidth;
			this->height = imgHeight;

			//Gen Texture
			glGenTextures(1, &this->id);
			glBindTexture(GL_TEXTURE_2D, this->id);

			//Parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			//Write data if exists
			if (Data) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			
			//Free Binding
			glActiveTexture(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		//Get Texture Id for manuall binding
		GLuint GetID(){
			return this->id;
		}
	};

	class Material {
	public:
		//Lighgting
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;

		int GlobalIlum;

		//Textures
		int hasTexture = 0;

		Texture2D* texDiff = nullptr;
		Texture2D* texSpec = nullptr;

	public:

		//Generation with lighting
		Material(vec3 ambient, vec3 diffuse, vec3 specular) {
			this->ambient = ambient;
			this->diffuse = diffuse;
			this->specular = specular;

			this->GlobalIlum = false;
		}

		//Generate with global illumination
		Material() {
			this->ambient = vec3(1.f);
			this->diffuse = vec3(0.f);
			this->specular = vec3(0.f);

			this->GlobalIlum = true;
		}

		//Deconstruct
		~Material() {
			
		}

		//Add Textures
		void AddTextures(Texture2D* diffuse, Texture2D* specular = nullptr) {
			this->hasTexture = 1;

			this->texDiff = diffuse;
			this->texSpec = specular;
		}

		//Returns textures
		vector<Texture2D*> GetTextures() {
			return { this->texDiff, this->texSpec };
		}

		//Binding for rendering
		void BindTextures() {
			if (texDiff != nullptr)
				texDiff->bind();

			if (texSpec != nullptr)
				texSpec->bind();
		}

		//Unbinding for clearing binded space
		void UnBindTextures() {
			if (texDiff != nullptr)
				texDiff->unbind();

			if (texSpec != nullptr)
				texSpec->unbind();
		}

		//Load all values to shader
		void sendToShader(Shader& shader) {
			
			//Lighting
			if (!GlobalIlum) {
				shader.setVec3f(this->ambient, "material.ambient");
				shader.setVec3f(this->diffuse, "material.diffuse");
				shader.setVec3f(this->specular, "material.specular");
			}

			//Textures
			if (texDiff != nullptr)
				shader.set1i(this->texDiff->GetUnit(), "material.diffuseTex");
			if (texSpec != nullptr)
				shader.set1i(this->texSpec->GetUnit(), "material.specularTex");

			//Main Settings
			shader.set1i(this->hasTexture, "material.hasTex");
			shader.set1i((this->texSpec != nullptr), "material.usesSpec");
			shader.set1i(this->GlobalIlum, "material.GlobalIllumination");
		}
	};
}