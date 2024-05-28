#include <Unified-Engine/UI/Elements/Panel.h>
#include <Unified-Engine/UI/UIContoller.h>

#include <Unified-Engine/debug.h>

using namespace UnifiedEngine;
using namespace UnifiedEngine::UI;

int Panel::Render(GUI* RenderInfo){
    if(!this->ShaderObj){
        // Create one using information given
        this->ShaderObj = new ShaderObject(RenderInfo->ShaderElement);
    }

    //Load Shader
    if(this->ShaderObj)
        this->ShaderObj->Toggle();

    if(this->VAO){
        //Bind Buffers
        glBindVertexArray(this->VAO);
        
        //Use Method Based on Indicies or not
        if (this->EBO)
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 4 Vertices but 6 Indices
        else
            glDrawArrays(GL_TRIANGLES, 0, 6); // 6 Vertices are defined

        //Clearing
        glBindVertexArray(0);
    }

    if(this->ShaderObj)
        this->ShaderObj->Toggle();

    for(auto* c : children){
        c->Render(RenderInfo);
    }
    return 0;
}
int Panel::Update(GUI* RenderInfo){
    for(auto* c : children){
        c->Update(RenderInfo);
    }
    return 0;
}

Panel::Panel(Element* parent, std::vector<Element*> children, glm::vec2 Pos, glm::vec2 Size, glm::vec4 Colour)
    : Element(parent, children, Pos, Size), Colour(Colour)
{
    if(Size.x == 0 || Size.y == 0){
        return;
    }

    // Create a set of indices and vertices
    std::vector<UIVertex> Vertices = {
        UIVertex{glm::vec3{Pos.x, Pos.y, 0.f}, Colour, glm::vec2{0.f, 0.f}}, // ⌈
        UIVertex{glm::vec3{Pos.x + Size.x, Pos.y, 0.f}, Colour, glm::vec2{0.f, 0.f}}, // ⌉
        UIVertex{glm::vec3{Pos.x, Pos.y + Size.y, 0.f}, Colour, glm::vec2{0.f, 0.f}}, // ⌊
        UIVertex{glm::vec3{Pos.x + Size.x, Pos.y + Size.y, 0.f}, Colour, glm::vec2{0.f, 0.f}}  // ⌋
    };
    std::vector<int> Indices = {
        2, 1, 0, // ⌈/
        2, 3, 1  // /⌋
    };

    // Setup Buffers
    GenerateBuffers(Vertices, Indices);
}
Panel::~Panel(){

}

void Panel::SetPos(glm::vec2 NewPos){
    Pos = NewPos;
}
void Panel::SetSize(glm::vec2 NewSize){
    Size = NewSize;
}
void Panel::SetColour(glm::vec4 NewCol){
    Colour = NewCol;
}