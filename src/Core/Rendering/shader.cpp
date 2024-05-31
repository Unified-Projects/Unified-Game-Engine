#include <Unified-Engine/Core/Rendering/shader.h>
#include <Unified-Engine/Core/config.h>
#include <Unified-Engine/debug.h>

namespace UnifiedEngine
{
    // Standard shaders
    const char* STANDARD_VERTEXT_SHADER_CODE = "#version 460\n\nlayout (location = 0) in vec3 vertex_position;\nlayout (location = 1) in vec3 vertex_color;\nlayout (location = 2) in vec2 vertex_texcoord;\nlayout (location = 3) in vec3 vertex_normal;\n\nout vec3 vs_position;\nout vec3 vs_color;\nout vec2 vs_texcoord;\nout vec3 vs_normal;\n\nuniform mat4 ModelMatrix;\nuniform mat4 ViewMatrix;\nuniform mat4 ProjectionMatrix;\n\nvoid main(){\n	vs_position = vec4(ModelMatrix * vec4(vertex_position, 1.f)).xyz;\n	vs_color = vertex_color;\n	vs_texcoord = vec2(vertex_texcoord.x, vertex_texcoord.y * -1.f);\n	vs_normal = mat3(ModelMatrix) * vertex_normal;\n\n	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vertex_position, 1.f);\n}";
    const char* STANDARD_FRAGMENT_SHADER_CODE = "#version 460\n\n in vec3 vs_position;\n in vec3 vs_color;\n in vec2 vs_texcoord;\n in vec3 vs_normal;\n\n out vec4 fs_color;\n\n uniform vec3 CameraPosition;\n uniform vec3 CameraFront;\n\nvoid main(){\n	//Final\n	fs_color = vec4(vs_color, 1.f);\n\n	if(fs_color.a==0.0) discard;\n	\n	// fs_color = vec4(1.f, 1.f, 1.f, 1.f);\n}";

    const char* STANDARD_VERTEX_UI_SHADER_CODE = "#version 460\nlayout (location = 0) in vec3 vertex_position;\nlayout (location = 1) in vec4 vertex_color;\nlayout (location = 2) in vec2 vertex_texcoord;\nout vec3 vs_position;\nout vec4 vs_color;\nout vec2 vs_texcoord;\nvoid main(){\nvs_position = vertex_position;\nvs_color = vertex_color;\nvs_texcoord = vertex_texcoord;\ngl_Position = vec4(vertex_position,1.0);\n}";
    const char* STANDARD_FRAGMENT_UI_SHADER_CODE = "#version 460\nin vec3 vs_position;\nin vec4 vs_color;\nin vec2 vs_texcoord;\nout vec4 fs_color;\nuniform sampler2D Texture;\nuniform vec2[4] UVMap;\nvoid main(){\n// fs_color = texture(Texture, vs_texcoord);\n// fs_color = vec4(0.f, 0.f, 0.f, 1.f);\nfs_color = vs_color;\nif(fs_color.a==0.0) discard;\n}";

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
        std::string str_src;
        if(fileLoc && strcmp("UI", fileLoc)){
            str_src = this->loadShaderSource(fileLoc);
        }
        else{
            //Change the src version to correct
            std::string version = std::to_string(__GLOBAL_CONFIG__.VersionMajor) + std::to_string(__GLOBAL_CONFIG__.VersionMinor) + "0";
            if(type == GL_VERTEX_SHADER){
                if(fileLoc)
                    str_src = STANDARD_VERTEX_UI_SHADER_CODE;
                else
                    str_src = STANDARD_VERTEXT_SHADER_CODE;
            }
            else{
                if(fileLoc)
                    str_src = STANDARD_FRAGMENT_UI_SHADER_CODE;
                else
                    str_src = STANDARD_FRAGMENT_SHADER_CODE;
            }
            //Replace Version
            str_src.replace(str_src.find("#version"), 12, ("#version " + version));
        }
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

        if (geometryFile != nullptr) {
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
    void Shader::setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose)
    {
        this->use();

        //Sets a mat3
        glUniformMatrix3fv(glGetUniformLocation(this->programID, name), 1, transpose, value_ptr(value));

        this->unbind();
    }

    //Setting a mat4 to a unifrom in the shader
    void Shader::setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose)
    {
        this->use();

        //Sets a mat4
        glUniformMatrix4fv(glGetUniformLocation(this->programID, name), 1, transpose, value_ptr(value));

        this->unbind();
    }
} // namespace UnifiedEngine
