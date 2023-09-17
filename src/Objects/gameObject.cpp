#include <Unified-Engine/Objects/gameObject.h>
#include <Unified-Engine/Core/instance.h>
#include <Unified-Engine/debug.h>

using namespace UnifiedEngine;

int GameObject::GenerateVAOBuffers(){
    //Test if already generated and if so clear all the buffers
    if (this->VAO) {
        glDeleteBuffers(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);

        //Clear EBO Buffer as well (Uses this method to stop problems if mesh is updated to not have indicices)
        if (this->EBO)
            glDeleteBuffers(1, &this->EBO);
    }

    //Create new buffers
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    //Copy new buffer data
    glBufferData(GL_ARRAY_BUFFER, this->mesh.vertices.size() * sizeof(Vertex), this->mesh.vertices.data(), GL_STATIC_DRAW);

    //If we use indicies for vertexes then we need to create a EBO buffer
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

    //Unbind for use with other objects
    glBindVertexArray(0);

    return 0;
}

GameObject::GameObject(Mesh _mesh, ShaderObject* _shader)
    : ObjectComponent(nullptr, OBJECT_GAME_OBJECT)
{
    //Initialse Values
    this->mesh = std::move(_mesh);
    this->shader = _shader;

    this->transformOld = this->transform;

    if(this->shader){
        this->shader->Parent = this;
        this->NoShader = false;
    }

    if(this->mesh.vertices.size())
        this->GenerateVAOBuffers();
}

GameObject::GameObject(GameObject* _parent, Mesh _mesh, ShaderObject* _shader)
    : ObjectComponent(_parent, OBJECT_GAME_OBJECT)
{
    //Initialse Values
    this->mesh = std::move(_mesh);
    this->shader = _shader;

    this->transformOld = this->transform;
    
    if(this->shader){
        this->shader->Parent = this;
        this->NoShader = false;
    }

    // this->Parent->Children.push_back(this);

    if(this->mesh.vertices.size())
        this->GenerateVAOBuffers();
}

GameObject::~GameObject(){

}

glm::mat4 CalculateModelMatrix(Transform transform, glm::vec3 origin){
    //Intialiser
    glm::mat4 Matrix(1.f);

    //Translations
    // Matrix = translate(Matrix, transform.Position);
    Matrix = glm::translate(Matrix, origin);
    Matrix = glm::rotate(Matrix, glm::radians(transform.Rotation.x), glm::vec3(1.f, 0.f, 0.f));
    Matrix = glm::rotate(Matrix, glm::radians(transform.Rotation.y), glm::vec3(0.f, 1.f, 0.f));
    Matrix = glm::rotate(Matrix, glm::radians(transform.Rotation.z), glm::vec3(0.f, 0.f, 1.f));
    Matrix = glm::translate(Matrix, transform.Position - origin);
    Matrix = glm::scale(Matrix, transform.Scale);

    //Return
    return Matrix;
}

int GameObject::Update(){
    this->ModelMatrix = CalculateModelMatrix(this->transform, this->transform.Position);
    // this->ModelMatrix = CalculateModelMatrix(this->transform, glm::vec3(0.0f));

    //Children
    this->UpdateC();

    if(this->NoShader && this->shader){
        this->NoShader = false;
        this->shader->Parent = this;
    }

    this->transformOld = this->transform;

    return 0;
}

int GameObject::Render(){
    if (this->Enabled) {
        //Update Shader Values
        if(this->shader)
            this->shader->PassArgs();

        //Load Shader
        if(this->shader)
            this->shader->Toggle();

        if(this->mesh.vertices.size()){
            //Bind Buffers
            glBindVertexArray(this->VAO);
            
            //Use Method Based on Indicies or not
            if (this->mesh.indices.size() > 0)
                glDrawElements(GL_TRIANGLES, this->mesh.indices.size(), GL_UNSIGNED_INT, 0);
            else
                glDrawArrays(GL_TRIANGLES, 0, this->mesh.vertices.size());

            //Clearing
            glBindVertexArray(0);
        }

        if(this->shader)
            this->shader->Toggle();

        //Children
        this->RenderC();
    }

    return 0;
}