#include <Unified-Engine/UI/Elements/Element.h>
#include <Unified-Engine/UI/UIContoller.h>

using namespace UnifiedEngine;
using namespace UnifiedEngine::UI;

Element::Element(Element* parent, std::vector<Element*> children, glm::vec2 Pos, glm::vec2 Size)
    : parent(parent), children(children), Pos(Pos), Size(Size)
{
    Element* iter = this;
    while(iter->parent){
        this->ZIndex-=1;
        iter = iter->parent;
    }
}
Element::~Element(){
    for(auto* c : children){
        delete c;
    }
    children.clear();
}

int Element::Render(GUI* RenderInfo){
    for(auto* c : children){
        c->Render(RenderInfo);
    }
    return 0;
}

int Element::Update(GUI* RenderInfo){
    for(auto* c : children){
        c->Update(RenderInfo);
    }
    return 0;
}

void Element::GenerateBuffers(std::vector<UIVertex> Vertices, std::vector<int> Indices){
    for(auto& v : Vertices){
        v.Pos.z = ZIndex;

        // TODO ALSO Relational sizes and positions
    }

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
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(UIVertex), Vertices.data(), GL_STATIC_DRAW);

    //If we use indicies for vertexes then we need to create a EBO buffer
    if (Indices.size() > 0) {
        glGenBuffers(1, &this->EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(GLuint), Indices.data(), GL_STATIC_DRAW);
    }

    //Split Data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(UIVertex), (GLvoid*)offsetof(UIVertex, Pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(UIVertex), (GLvoid*)offsetof(UIVertex, Colour));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(UIVertex), (GLvoid*)offsetof(UIVertex, UV));
    glEnableVertexAttribArray(2);

    //Unbind for use with other objects
    glBindVertexArray(0);

    return;
}