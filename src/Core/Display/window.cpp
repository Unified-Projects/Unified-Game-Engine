#include <Unified-Engine/Core/Display/window.h>
#include <Unified-Engine/Core/instance.h>
#include <Unified-Engine/debug.h>
#include <Unified-Engine/input/input.h>
#include <string.h>

using namespace UnifiedEngine;

/**
 * @brief Loads the window object to the Game
 * 
 * @return int (-1 for error)
 */
int Window::Load(){
    if(!__GAME__GLOBAL__INSTANCE__)
        return -1;

    if(__GAME__GLOBAL__INSTANCE__->__windows.size() > 0){
        // WARN("Multiple Windows Detected, Only One Window Supported");
        // return -1;
        // Could be debugger
        return 1;
    }

    __GAME__GLOBAL__INSTANCE__->__windows.push_back(this);
    this->loaded = true;

    //Setup Input
    __GAME__GLOBAL__INSTANCE__->Input = new InputClass(this);
    InputPointer = __GAME__GLOBAL__INSTANCE__->Input;

    if(!__GAME__GLOBAL__INSTANCE__->gladInited){
        //Ensure Glad Gets Toggled post window
        __GAME__GLOBAL__INSTANCE__->_Init_Glad();
    }

    return 0;
}

/**
 * @brief Unloads the window object from the Game
 * 
 * @return int (-1 for error)
 */
int Window::Unload(){
    if(!__GAME__GLOBAL__INSTANCE__)
        return -1;

    __GAME__GLOBAL__INSTANCE__->__windows.remove(this);
    this->loaded = false;

    return 0;
}

/**
 * @brief Construct a new Window object for the Game
 * 
 * @param config 
 */
Window::Window(WindowConfig config)
    : GameInteractionObject(__GIO_WINDOW_OBJECT_ID__)
{
    this->__mainConfig = {};

    //Sizing
    this->__mainConfig.x = config.x;
    this->__mainConfig.y = config.y;

    //Resolution
    this->__mainConfig.res_x = config.res_x;
    this->__mainConfig.res_y = config.res_y;

    if(this->__mainConfig.res_x == 0 || this->__mainConfig.res_y == 0){
        WARN("Cannot set display to a resolution of 0");
        this->__mainConfig.res_x = config.x;
        this->__mainConfig.res_y = config.y;
    }

    //Titlebar
    this->__mainConfig.title = new char[strlen(config.title) + 1];
    memcpy((void*)this->__mainConfig.title, (void*)config.title, strlen(config.title));
    this->__mainConfig.title[strlen(config.title)] = 0;

    //Window Settings
    this->__mainConfig.resizable = config.resizable;
    this->__mainConfig.fullScreen = config.fullScreen;
    this->__mainConfig.vsync = config.vsync;
    this->__mainConfig.fps = config.fps;
    this->__mainConfig.backgroundColor = config.backgroundColor;
    this->__mainConfig.monitor = config.monitor;
        
    //Multi-window setup
    this->__mainConfig.sharedContext = config.sharedContext;
    // this->__mainConfig.sharedContext = NULL;

    //Create Context
    this->__windowContext = glfwCreateWindow(this->__mainConfig.x, this->__mainConfig.y, this->__mainConfig.title, this->__mainConfig.monitor, this->__mainConfig.sharedContext);
    this->Activate();

    //Update Hints
    this->UpdateWindow();

    //Interact with main instance
    if(this->Load() < 0){
        FAULT("Window Object Failed To Attach To Game", "::Game Object Not Found");
    }
}

//Configurators
int Window::LoadWindowConfig(WindowConfig config){

    this->__mainConfig = {};

    //Sizing
    this->__mainConfig.x = config.x;
    this->__mainConfig.y = config.y;

    //Resolution
    this->__mainConfig.res_x = config.res_x;
    this->__mainConfig.res_y = config.res_y;

    if(this->__mainConfig.res_x == 0 || this->__mainConfig.res_y == 0){
        WARN("Cannot set display to a resolution of 0");
        this->__mainConfig.res_x = config.x;
        this->__mainConfig.res_y = config.y;
    }

    //Titlebar
    this->__mainConfig.title = new char[strlen(config.title) + 1];
    memcpy((void*)this->__mainConfig.title, (void*)config.title, strlen(config.title));
    this->__mainConfig.title[strlen(config.title)] = 0;

    //Window Settings
    this->__mainConfig.resizable = config.resizable;
    this->__mainConfig.fullScreen = config.fullScreen;
    this->__mainConfig.vsync = config.vsync;
    this->__mainConfig.fps = config.fps;
    this->__mainConfig.backgroundColor = config.backgroundColor;
    this->__mainConfig.monitor = config.monitor;
        
    //Multi-window setup
    this->__mainConfig.sharedContext = config.sharedContext;

    //Update Hints
    this->UpdateWindow();

    return 0;
}

/**
 * @brief Destroy the Window
 * 
 */
Window::~Window(){
    //Remove from main game instance
    this->Unload();

    //Clear Needed
    free((void*)this->__mainConfig.title);
}

/**
 * @brief Makes context current
 * 
 * @return int 
 */
int Window::Activate(){
    glfwMakeContextCurrent(this->__windowContext);

    return 0;
}

/**
 * @brief Updates the window settings based off config
 * 
 */
void Window::UpdateWindow(){
    glfwWindowHint(GLFW_RESIZABLE, this->__mainConfig.resizable);
    
    // Vsync
    // if(!this-__mainConfig.vsync){
        // glfwSwapInterval(0);
        glfwWindowHint(GLFW_DOUBLEBUFFER, this->__mainConfig.vsync);
    // }
}