#include <Unified-Engine/core/instance.h>
#include <Unified-Engine/Objects/gameObject.h>

int main(){
    UnifiedEngine::__GLOBAL_CONFIG__.VersionMajor = 4;
    UnifiedEngine::__GLOBAL_CONFIG__.VersionMinor = 6;

    UnifiedEngine::__INIT__ENGINE();

    UnifiedEngine::WindowConfig WinConf = {.x = 1260, .y = 720, .res_x = 0, .res_y = 0, .title = "Test Program", .resizable = true, .fullScreen = false, .vsync = true, .fps = 60};
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
            //TODO: Call some sort of deinitializer (UnifiedEngine::Terminate())
            exit(10);
        }

        // Your game code

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