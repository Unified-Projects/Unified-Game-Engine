#pragma once    

#include <Unified-Engine/Core/Display/window.h>
#include <Unified-Engine/includeGL.h>
#include <Unified-Engine/UI/Elements/Panel.h>
#include <Unified-Engine/Core/Rendering/shader.h>


namespace UnifiedEngine
{
    namespace UI
    {
        class GUI{
            friend Element;
            friend Panel;
        protected:
            // For rendering
            Window* RenderWindow = nullptr;
            Shader* ShaderElement = nullptr;

        public:
            UI::Panel* RootWindow = nullptr;

        public:
            GUI(UnifiedEngine::Window* RenderWindow);
            ~GUI();

        public:
            int Update();
            int Render();
        };
    } // namespace UI
    
} // namespace UnifiedEngine
