#pragma once

#include <Unified-Engine/Objects/objectComponent.h>
#include <Unified-Engine/Objects/Mesh/mesh.h>
#include <Unified-Engine/Objects/Components/transform.h>
#include <Unified-Engine/Objects/Components/shaderObject.h>
#include <string>
#include <glm/mat4x4.hpp>

namespace UnifiedEngine
{
    class GameObject : public ObjectComponent{
        friend ShaderObject;
        friend ObjectComponent;
    protected:
        //Buffers
		GLuint VAO = 0;
		GLuint VBO = 0;
		GLuint EBO = 0;

        //To be updated through functions to prevent memory leaks with updating VAO
        Mesh mesh = {};

        //Matricies
        glm::mat4 ModelMatrix;
    protected: //Math and Mesh Functions
        int GenerateVAOBuffers();

        bool NoShader = true;
        Transform transformOld = {};
        
    public:
        //Game Object Specifics
        Transform transform = {};

        std::string Name = "";
        std::string Tag = "";

        //To fix rendering problems its not part of children and required
        ShaderObject* shader = nullptr;

    public:
        GameObject(Mesh _mesh, ShaderObject* _shader);
        GameObject(GameObject* _parent, Mesh _mesh, ShaderObject* _shader);
        ~GameObject();

    public:
        int Update() override;
        int Render() override;
    };
} // namespace UnifiedEngine
