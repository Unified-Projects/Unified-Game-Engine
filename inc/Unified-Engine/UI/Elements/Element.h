#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <Unified-Engine/Objects/Components/shaderObject.h>

namespace UnifiedEngine
{
    namespace UI
    {
        struct UIVertex{
            glm::vec3 Pos;
            glm::vec4 Colour;
            glm::vec2 UV;
        };

        class Element{
        public:
            virtual int Render(class GUI* RenderInfo);
            virtual int Update(class GUI* RenderInfo);

            // Loaded On First Render!
            ShaderObject* ShaderObj = nullptr;

        public:
            Element(Element* parent = nullptr, std::vector<Element*> children = {}, glm::vec2 Pos = {}, glm::vec2 Size = {});
            virtual ~Element();

        public:
            std::vector<Element*> children = {};
            Element* parent = nullptr;

        protected:
            glm::vec2 Pos = {0, 0};
            glm::vec2 Size = {0, 0};
            int ZIndex = 0;

        protected:
            GLuint VAO = 0;
            GLuint VBO = 0;
            GLuint EBO = 0;

            void GenerateBuffers(std::vector<UIVertex> Vertices, std::vector<int> Indices);

        public:
            inline virtual void SetPos(glm::vec2 NewPos) {Pos = NewPos;}
            inline virtual void SetSize(glm::vec2 NewSize) {Size = NewSize;}

            inline glm::vec2 GetPos() {return Pos;}
            inline glm::vec2 GetSize() {return Size;}
        };
    } // namespace UI
    
} // namespace UnifiedEngine
