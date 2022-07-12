#pragma once

#include <stdint.h>

#include <Unified-Engine/includeGL.h>
#include <Unified-Engine/Core/gameInteractionObject.h>
#include <Unified-Engine/Core/Display/color.h>

namespace UnifiedEngine
{   
    struct WindowConfig
    {   
        //Sizing
        uint32_t x = 0;
        uint32_t y = 0;

        //Resolution
        uint32_t res_x = 0;
        uint32_t res_y = 0;

        //Titlebar
        char* title = nullptr;

        //Window Settings
        bool resizable = false;
        bool fullScreen = false;
        bool vsync = false;
        int fps = -1;
        Color backgroundColor = {0.0f, 0.0f, 0.0f, 0.0f};
        GLFWmonitor* monitor = NULL;
        
        //Multi-window setup
        GLFWwindow* sharedContext = NULL;
    };
    

    class Window : public GameInteractionObject{
    private:
        //Data
        GLFWwindow* __windowContext = nullptr;

        //Configs
        WindowConfig __mainConfig = {};

    public:
        //Constructors
        Window(WindowConfig config);
        ~Window();

        //Activator
        int Activate();
        inline GLFWwindow* Context(){return this->__windowContext;}
        inline WindowConfig Config(){return this->__mainConfig;}
    public:
        //Configurators
        int LoadWindowConfig(WindowConfig Config);

    private:
        int Load() override;
        int Unload() override;
        void UpdateWindow();
    };
} // namespace UnifiedEngine
