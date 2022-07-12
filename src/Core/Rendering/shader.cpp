#include <Unified-Engine/Core/Rendering/shader.h>
#include <Unified-Engine/Core/config.h>
#include <Unified-Engine/debug.h>

namespace UnifiedEngine
{
    //Gen Shader
    std::string Shader::loadShaderSource(const char* fileLoc) {
        std::string temp = "";
        std::string src = "";

        std::ifstream in_file;

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
        std::string version = std::to_string(__GLOBAL_CONFIG__.VersionMajor) + std::to_string(__GLOBAL_CONFIG__.VersionMinor) + "0";

        //Replace Version
        src.replace(src.find("#version"), 12, ("#version " + version));
        
        //Return it
        return src;
    }

    //Load
    GLuint Shader::loadShader(GLenum type, const char* fileLoc) {
        char infoLog[512];
        GLint success;

        //Create a shader
        GLuint shader = glCreateShader(type);

        //Load the Src
        std::string str_src = this->loadShaderSource(fileLoc);
        const GLchar* Src = str_src.c_str();

        //Compile the shader
        glShaderSource(shader, 1, &Src, NULL);
        glCompileShader(shader);

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            FAULT("SHADER:", type, ":FAILED TO LOAD SUCCESSFULLY::", infoLog);
        }

        //Return the shader id
        return shader;
    }

    //Link
    void Shader::linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader) {
        char infoLog[512];
        GLint success;

        //Create the program
        this->programID = glCreateProgram();

        //Bind the program to shaders
        glAttachShader(this->programID, vertexShader);

        if (geometryShader)
            glAttachShader(this->programID, geometryShader);

        glAttachShader(this->programID, fragmentShader);

        //Link the program
        glLinkProgram(this->programID);

        glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(this->programID, 512, NULL, infoLog);
            FAULT("SHADER::FAILED TO LINK SUCCESSFULLY::", infoLog);
        }

        //Unbind
        glUseProgram(0);
    }

    Shader::Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile) {
        //Set Defaults
        GLuint vertexShader = 0;
        GLuint geometryShader = 0;
        GLuint fragmentShader = 0;

        //Load Specific shaders
        vertexShader = this->loadShader(GL_VERTEX_SHADER, vertexFile);

        if (std::strlen(geometryFile) > 3) {
            geometryShader = this->loadShader(GL_GEOMETRY_SHADER, geometryFile);
        }

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

    Shader::~Shader() {
        //Delete the program
        glDeleteProgram(this->programID);
    }

    //Linker
    void Shader::use() {
        //Bind shader
        glUseProgram(this->programID);
    }

    //Unlink
    void Shader::unbind() {
        //Unbinds the shader
        glUseProgram(0);
    }

    //Setting a integer to a unifrom in the shader
    void Shader::set1i(GLint value, const GLchar* name)
    {
        this->use();

        //Sets a integer
        glUniform1i(glGetUniformLocation(this->programID, name), value);

        this->unbind();
    }

    //Setting a float to a unifrom in the shader
    void Shader::set1f(GLfloat value, const GLchar* name)
    {
        this->use();

        //Sets a float
        glUniform1f(glGetUniformLocation(this->programID, name), value);

        this->unbind();
    }

    //Setting a vec2 to a unifrom in the shader
    void Shader::setVec2f(glm::fvec2 value, const GLchar* name)
    {
        this->use();

        //Sets a vec2
        glUniform2fv(glGetUniformLocation(this->programID, name), 1, value_ptr(value));

        this->unbind();
    }

    //Setting a vec3 to a unifrom in the shader
    void Shader::setVec3f(glm::fvec3 value, const GLchar* name)
    {
        this->use();

        //Sets a vec3
        glUniform3fv(glGetUniformLocation(this->programID, name), 1, value_ptr(value));

        this->unbind();
    }

    //Setting a vec4 to a unifrom in the shader
    void Shader::setVec4f(glm::fvec4 value, const GLchar* name)
    {
        this->use();

        //Sets a vec4
        glUniform4fv(glGetUniformLocation(this->programID, name), 1, value_ptr(value));

        this->unbind();
    }

    //Setting a mat3 to a unifrom in the shader
    void Shader::setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE)
    {
        this->use();

        //Sets a mat3
        glUniformMatrix3fv(glGetUniformLocation(this->programID, name), 1, transpose, value_ptr(value));

        this->unbind();
    }

    //Setting a mat4 to a unifrom in the shader
    void Shader::setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE)
    {
        this->use();

        //Sets a mat4
        glUniformMatrix4fv(glGetUniformLocation(this->programID, name), 1, transpose, value_ptr(value));

        this->unbind();
    }
} // namespace UnifiedEngine
