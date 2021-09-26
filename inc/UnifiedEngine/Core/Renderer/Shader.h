#pragma once

//Includes
#include <string>
#include <fstream>
#include <vector>
#include "../OpenGL/OpenGLInc.h"
#include "../../Maths/Maths.h"

namespace UnifiedEngine {
	class Shader {
	private:
		//Ids
		GLuint ProgramID;

		//OpenGL
		const int versionMajor;
		const int versionMinor;

		//Gen Shader
		string loadShaderSource(const char* fileLoc) {
			string temp = "";
			string src = "";

			ifstream in_file;

			//Open The File
			in_file.open(fileLoc);

			//Read src
			if (in_file.is_open()) {
				while (getline(in_file, temp)) {
					src += temp + "\n";
				}
			}

			//Close File
			in_file.close();

			//Change the src version to correct
			string version = to_string(this->versionMajor) + to_string(this->versionMinor) + "0";
			
			//Replace Version
			src.replace(src.find("#version"), 12, ("#version " + version));
			
			//Return it
			return src;
		}

		//Load
		GLuint loadShader(GLenum type, const char* fileLoc) {
			char infoLog[512];
			GLint success;

			//Create a shader
			GLuint shader = glCreateShader(type);

			//Load the Src
			string str_src = this->loadShaderSource(fileLoc);
			const GLchar* Src = str_src.c_str();

			//Compile the shader
			glShaderSource(shader, 1, &Src, NULL);
			glCompileShader(shader);

			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
			}

			//Return the shader id
			return shader;
		}

		//Link
		void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader) {
			char infoLog[512];
			GLint success;

			//Create the program
			this->ProgramID = glCreateProgram();

			//Bind the program to shaders
			glAttachShader(this->ProgramID, vertexShader);

			if (geometryShader)
				glAttachShader(this->ProgramID, geometryShader);

			glAttachShader(this->ProgramID, fragmentShader);

			//Link the program
			glLinkProgram(this->ProgramID);

			glGetProgramiv(this->ProgramID, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(this->ProgramID, 512, NULL, infoLog);
			}

			//Unbind
			glUseProgram(0);
		}

	public:
		const char* Name;

		//Con/Destructors
		Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile = "")
			: versionMajor(GLMajor), versionMinor(GLMinor)
		{
			//Set Defaults
			GLuint vertexShader = 0;
			GLuint geometryShader = 0;
			GLuint fragmentShader = 0;

			//Load Specific shaders
			vertexShader = this->loadShader(GL_VERTEX_SHADER, vertexFile);

			if (geometryFile != "")
				geometryShader = this->loadShader(GL_GEOMETRY_SHADER, geometryFile);

			fragmentShader = this->loadShader(GL_FRAGMENT_SHADER, fragmentFile);

			//Link Them
			this->linkProgram(vertexShader, geometryShader, fragmentShader);

			//Delete them
			glDeleteShader(vertexShader);
			glDeleteShader(geometryShader);
			glDeleteShader(fragmentShader);

			//Unbind
			glUseProgram(0);
		}

		~Shader() {
			//Delete the program
			glDeleteProgram(this->ProgramID);
		}

		//Get the Program
		inline GLuint getProgram() const {
			return this->ProgramID;
		}

		//Linker	
		void use() {
			//Bind shader
			glUseProgram(this->ProgramID);
		}

		//Unlink
		void unbind() {
			//Unbinds the shader
			glUseProgram(0);
		}

		//Setting a integer to a unifrom in the shader
		void set1i(GLint value, const GLchar* name)
		{
			this->use();

			//Sets a integer
			glUniform1i(glGetUniformLocation(this->ProgramID, name), value);

			this->unbind();
		}

		//Setting a float to a unifrom in the shader
		void set1f(GLfloat value, const GLchar* name)
		{
			this->use();

			//Sets a float
			glUniform1f(glGetUniformLocation(this->ProgramID, name), value);

			this->unbind();
		}

		//Setting a vec2 to a unifrom in the shader
		void setVec2f(fvec2 value, const GLchar* name)
		{
			this->use();

			//Sets a vec2
			glUniform2fv(glGetUniformLocation(this->ProgramID, name), 1, value_ptr(value));

			this->unbind();
		}

		//Setting a vec3 to a unifrom in the shader
		void setVec3f(fvec3 value, const GLchar* name)
		{
			this->use();

			//Sets a vec3
			glUniform3fv(glGetUniformLocation(this->ProgramID, name), 1, value_ptr(value));

			this->unbind();
		}

		//Setting a vec4 to a unifrom in the shader
		void setVec4f(fvec4 value, const GLchar* name)
		{
			this->use();

			//Sets a vec4
			glUniform4fv(glGetUniformLocation(this->ProgramID, name), 1, value_ptr(value));

			this->unbind();
		}

		//Setting a mat3 to a unifrom in the shader
		void setMat3fv(mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE)
		{
			this->use();

			//Sets a mat3
			glUniformMatrix3fv(glGetUniformLocation(this->ProgramID, name), 1, transpose, value_ptr(value));

			this->unbind();
		}

		//Setting a mat4 to a unifrom in the shader
		void setMat4fv(mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE)
		{
			this->use();

			//Sets a mat4
			glUniformMatrix4fv(glGetUniformLocation(this->ProgramID, name), 1, transpose, value_ptr(value));

			this->unbind();
		}
	};
}