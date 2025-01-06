#include <Unified-Engine/core/instance.h>

#include <Unified-Engine/Objects/gameObject.h>
#include <Unified-Engine/Objects/Mesh/Defaults/cube.h>
#include <Unified-Engine/Core/Rendering/shader.h>
#include <Unified-Engine/Objects/Components/shaderObject.h>

#include <Unified-Engine/input/input.h>

#include <Unified-Engine/Objects/scriptObject.h>
#include <Unified-Engine/Core/time.h>

int main(){
    UnifiedEngine::__GLOBAL_CONFIG__.VersionMajor = 4;
    UnifiedEngine::__GLOBAL_CONFIG__.VersionMinor = 1;

    UnifiedEngine::__INIT__ENGINE();

    // Window Setup
    UnifiedEngine::WindowConfig WinConf = {.x = 1260, .y = 720, .res_x = 1260, .res_y = 720, .title = (char*)"Test Program", .resizable = false, .fullScreen = false, .vsync = true, .fps = 60};
    WinConf.backgroundColor = {0, 0, 0};

    UnifiedEngine::Window GameWindow(WinConf);

    // Skybox
    UnifiedEngine::SkyboxSolidColor box(glm::vec3(135, 206, 235));
    UnifiedEngine::__GAME__GLOBAL__INSTANCE__->skybox = &box;

    //Camera
    UnifiedEngine::Camera Cam;
    UnifiedEngine::instantiate(&Cam);
    
    // Game loop
    while (!glfwWindowShouldClose(GameWindow.Context()))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        if(UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Update()){
            FAULT("GAME_INSTANCE::FAILED TO UPDATE!");
            exit(10);
            //TODO: Call some sort of deinitializer (UnifiedEngine::Terminate())
        }

        if(UnifiedEngine::InputPointer->Keyboard.KeyPressed(UnifiedEngine::Key_ESCAPE)){
            break;
        }

        if(UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Render()){
            FAULT("GAME_INSTANCE::FAILED TO RENDER!");
            //TODO: Call some sort of deinitializer (UnifiedEngine::Terminate())
            exit(11);
        }
    }

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();

    return 0;
}
