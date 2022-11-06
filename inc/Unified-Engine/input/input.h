#pragma once

#include <Unified-Engine/Core/Display/window.h>
#include <Unified-Engine/input/mouse.h>
#include <Unified-Engine/input/keyboard.h>

namespace UnifiedEngine
{
    class Window;

    class InputClass{
    private:
        Window* WindowObject;

    public:
        MouseController Mouse;
        KeyboardController Keyboard;
    
    public:
        InputClass(Window* windowObj);
        ~InputClass();
    };

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    extern InputClass* InputPointer;
} // namespace UnifiedEngine
