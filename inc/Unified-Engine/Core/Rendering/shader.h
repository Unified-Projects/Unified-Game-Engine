#pragma once

#include <Unified-Engine/includeGL.h>
#include <string>
#include <fstream>
#include <vector>

#include <GLM/glm.hpp>
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>
#include <GLM/mat4x4.hpp>
#include <GLM/gtc/type_ptr.hpp>
namespace UnifiedEngine
{
    class Shader{
    public:
        //Ids
		GLuint programID = 0;
    
    private:
        //Gen Shader
		std::string loadShaderSource(const char* fileLoc);

		//Load
		GLuint loadShader(GLenum type, const char* fileLoc);

		//Link
		void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);

    public:
        std::string name = "";

        Shader(const char* vertexFile = nullptr, const char* fragmentFile = nullptr, const char* geometryFile = nullptr);

		~Shader();

		//Get the Program
		inline GLuint getProgram() const {
			return this->programID;
		}

		//Linker
		void use();

		//Unlink
		void unbind();

		//Setting a integer to a unifrom in the shader
		void set1i(GLint value, const GLchar* name);

		//Setting a float to a unifrom in the shader
		void set1f(GLfloat value, const GLchar* name);

		//Setting a vec2 to a unifrom in the shader
		void setVec2f(glm::fvec2 value, const GLchar* name);

		//Setting a vec3 to a unifrom in the shader
		void setVec3f(glm::fvec3 value, const GLchar* name);

		//Setting a vec4 to a unifrom in the shader
		void setVec4f(glm::fvec4 value, const GLchar* name);

		//Setting a mat3 to a unifrom in the shader
		void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);

		//Setting a mat4 to a unifrom in the shader
		void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
    };
} // namespace UnifiedEngine
