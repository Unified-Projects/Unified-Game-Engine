#pragma once

#include <Unified-Engine/Core/Display/window.h>
#include <Unified-Engine/UI/UIContoller.h>

namespace UnifiedEngine
{
    namespace Debug
    {
        class DebugWindow{
        protected:
            Window* window = nullptr;
            WindowConfig Config;

        protected:
            bool DeltaTimeEnabled = false;

        protected:
            GLuint Framebuffer = 0;
            GLuint Renderbuffer = 0;
            GLuint Texture = 0;

        protected:
            UI::GUI* GUIInt = nullptr;

        public:
            DebugWindow(WindowConfig config);
            ~DebugWindow();

        public:
            int Update();
            int Render();
        };
    } // namespace Debug
    
} // namespace UnifiedEngine
