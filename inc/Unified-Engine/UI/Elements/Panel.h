#pragma once

#include <Unified-Engine/UI/Elements/Element.h>

#include <glm/vec4.hpp>

namespace UnifiedEngine
{
    namespace UI
    {
        class Panel : public Element{
        public:
            // Overrides of render/ update
            virtual int Render(class GUI* RenderInfo);
            virtual int Update(class GUI* RenderInfo);
        
        public:
            Panel(Element* parent = nullptr, std::vector<Element*> children = {}, glm::vec2 Pos = {}, glm::vec2 Size = {}, glm::vec4 Colour = {});
            ~Panel();

        protected:
            glm::vec4 Colour; // Alpha chanel
        
        public:
            virtual void SetPos(glm::vec2 NewPos);
            virtual void SetSize(glm::vec2 NewSize);
            virtual void SetColour(glm::vec4 NewCol);

            inline glm::vec4 GetColour() {return Colour;}
        };
    } // namespace UI
    
} // namespace UnifiedEngine
