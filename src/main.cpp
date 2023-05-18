#include <iostream>

#include <Unified-Engine/debug.h>
#include <Unified-Engine/core/instance.h>
#include <Unified-Engine/Core/Rendering/shader.h>
#include <Unified-Engine/Objects/gameObject.h>
#include <Unified-Engine/Objects/scriptObject.h>
#include <Unified-Engine/Objects/Mesh/Defaults/cube.h>
#include <Unified-Engine/Core/time.h>
#include <Unified-Engine/Objects/Components/material.h>
#include <Unified-Engine/Objects/Components/rigidbody.h>

#include <cstdlib>

using namespace UnifiedEngine;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//Test CameraScript

class CameraControl : public UnifiedEngine::ScriptableObject{
public:
    GameObject* OBJ;

    CameraControl(GameObject* Par, UnifiedEngine::ObjectComponent* Camera)
        : UnifiedEngine::ScriptableObject(Par)
    {
        OBJ = Par;
        //Lock mouse cursor
        // this->OBJ.Children.push_back(Parent);
        // this->OBJ.Children.push_back(Parent);

        OBJ = Par;
        OBJ->Name = "CamCam";

        // UnifiedEngine::Shader* shader = new Shader("./rsc/testVertex.glsl", "./rsc/testFragment.glsl");
        // UnifiedEngine::ShaderObject* shaderObj = new ShaderObject(shader);

        // OBJ->shader = shaderObj;

        instantiate(OBJ);

        this->OBJ->Children.push_back(Camera);
        Camera->Parent = OBJ;
    }

    int Update(){
        //Player Movement
        if (UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Input->Keyboard.KeyPressed(UnifiedEngine::Key_W))
            this->OBJ->transform.Position += 0.002f*UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->front/UnifiedEngine::Time.DeltaTime;
        if (UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Input->Keyboard.KeyPressed(UnifiedEngine::Key_A))
            this->OBJ->transform.Position -= 0.002f*UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->right/UnifiedEngine::Time.DeltaTime;
        if (UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Input->Keyboard.KeyPressed(UnifiedEngine::Key_S))
            this->OBJ->transform.Position -= 0.002f*UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->front/UnifiedEngine::Time.DeltaTime;
        if (UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Input->Keyboard.KeyPressed(UnifiedEngine::Key_D))
            this->OBJ->transform.Position += 0.002f*UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->right/UnifiedEngine::Time.DeltaTime;
        if (UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Input->Keyboard.KeyPressed(UnifiedEngine::Key_SPACE))
            this->OBJ->transform.Position += 0.002f*UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->up/UnifiedEngine::Time.DeltaTime;
        if (UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Input->Keyboard.KeyPressed(UnifiedEngine::Key_LEFT_SHIFT))
            this->OBJ->transform.Position -= 0.002f*UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->up/UnifiedEngine::Time.DeltaTime;
        

        //Player Rotation
        glm::vec2 mPos = UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Input->Mouse.GetPosition();

        //Update pitch yaw and roll
        UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->transform.Rotation.x += static_cast<GLfloat>(mPos.y) * (0.004 / UnifiedEngine::Time.DeltaTime);
        UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->transform.Rotation.y += static_cast<GLfloat>(mPos.x) * (0.004 / UnifiedEngine::Time.DeltaTime);

        if (UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->transform.Rotation.x > 89.f)
            UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->transform.Rotation.x = 89.f;
        else if (UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->transform.Rotation.x < -89.f)
            UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->transform.Rotation.x = -89.f;

        if (UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->transform.Rotation.y > 360.f || UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->transform.Rotation.y < -360.f)
            UnifiedEngine::__GAME__GLOBAL__INSTANCE__->GetMainCamera()->transform.Rotation.y = 0.f;

        //Resolution with scroll
        UnifiedEngine::WindowConfig conf = UnifiedEngine::__GAME__GLOBAL__INSTANCE__->__windows.front()->Config();

        int scroll = UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Input->Mouse.Scroll();

        if(scroll == 1){
            conf.res_x *= 2;
            conf.res_y *= 2;
        }
        else if(scroll == -1){
            conf.res_x /= 2;
            conf.res_y /= 2;
        }

        if (conf.res_x <= 80)
            conf.res_x = 80;
        if (conf.res_y <= 45)
            conf.res_y = 45;

        if (conf.res_x >= 1280)
            conf.res_x = 1280;
        if (conf.res_y >= 720)
            conf.res_y = 720;

        UnifiedEngine::__GAME__GLOBAL__INSTANCE__->__windows.front()->LoadWindowConfig(conf);

        return 0;
    }
};

void NewCube(glm::vec3 Pos, glm::vec3 Rot, glm::vec3 Scale){
    Mesh* mesh = new Cube();

    UnifiedEngine::Shader* shader = new Shader("./rsc/testVertex.glsl", "./rsc/testFragment.glsl");
    UnifiedEngine::ShaderObject* shaderObj = new ShaderObject(shader);
    UnifiedEngine::GameObject* gOBJ = new GameObject(*mesh, shaderObj);
    gOBJ->transform.Position = Pos;
    gOBJ->transform.Rotation = Rot;
    gOBJ->transform.Scale = Scale;
    // gOBJ.transform.Position.z -= 1;
    UnifiedEngine::instantiate(gOBJ);
}

// The MAIN function, from here we start the application and run the game loop
int main()
{
    UnifiedEngine::__GLOBAL_CONFIG__.VersionMajor = 4;
    UnifiedEngine::__GLOBAL_CONFIG__.VersionMinor = 6;

    UnifiedEngine::__INIT__ENGINE();

    /*
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
        Color backgroundColor = {0.0f, 0.0f, 0.0f, 1.0f};
        GLFWmonitor* monitor = NULL;
        
        //Multi-window setup
        GLFWwindow* sharedContext = NULL;
    */

    UnifiedEngine::WindowConfig WinConf = {.x = 1260, .y = 720, .res_x = 0, .res_y = 0, .title = "Test Program", .resizable = true, .fullScreen = false, .vsync = true, .fps = 60};
    WinConf.backgroundColor = {0, 0, 0};

    UnifiedEngine::SkyboxSolidColor box(glm::vec3(135, 206, 235));
    UnifiedEngine::__GAME__GLOBAL__INSTANCE__->skybox = &box;

    UnifiedEngine::Window GameWindow(WinConf);

    // Set the required callback functions
    glfwSetKeyCallback(GameWindow.Context(), key_callback);

    UnifiedEngine::Shader shader("./rsc/testVertex.glsl", "./rsc/text.frag.glsl");
    UnifiedEngine::ShaderObject shaderObj(&shader);

    Texture2D texture("./rsc/Test.png");
    Texture2DMaterial Mat(&shaderObj, &texture);

    UnifiedEngine::Mesh mesh;

    mesh = UnifiedEngine::Cube();
    for (auto i = mesh.vertices.begin(); i != mesh.vertices.end(); i++){
        (*i).uv = texture.UVs.UV[0];
        i++;
        (*i).uv = texture.UVs.UV[2];
        i++;
        (*i).uv = texture.UVs.UV[3];
        i++;
        (*i).uv = texture.UVs.UV[1];
    }
    
    UnifiedEngine::GameObject gOBJ(mesh, &shaderObj);
    UnifiedEngine::instantiate(&gOBJ);

    NewCube(glm::vec3(10, 0, 0), glm::vec3(0.0), glm::vec3(1));
    NewCube(glm::vec3(0, 10, 0), glm::vec3(0.0), glm::vec3(1));
    NewCube(glm::vec3(0, 0, 10), glm::vec3(0.0), glm::vec3(1));
    NewCube(glm::vec3(-10, 0, 0), glm::vec3(0.0), glm::vec3(1));
    NewCube(glm::vec3(0, -10, 0), glm::vec3(0.0), glm::vec3(5, 1, 5));
    NewCube(glm::vec3(0, 0, -10), glm::vec3(0.0), glm::vec3(1));

    //Camera
    UnifiedEngine::Camera Cam;

    // Cam.Position = {0.f, 0.f, 0.f};

    UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Input->Mouse.Cursor.Locked();
    // UnifiedEngine::Shader* shader = new Shader("./rsc/testVertex.glsl", "./rsc/testFragment.glsl");
    // UnifiedEngine::ShaderObject* shaderObj = new ShaderObject(shader);
    GameObject CamOBJ(Mesh{}, nullptr);
    // RigidBody rb(&CamOBJ);
    CameraControl Controller(&CamOBJ, &Cam);

    Mesh* child_mesh = new Cube();

    UnifiedEngine::Shader* child_shader = new Shader("./rsc/testVertex.glsl", "./rsc/testFragment.glsl");
    UnifiedEngine::ShaderObject* child_shaderObj = new ShaderObject(child_shader);
    UnifiedEngine::GameObject* child_gOBJ = new GameObject(*child_mesh, child_shaderObj);
    child_gOBJ->transform.Position = glm::vec3(0, 0, -5);
    child_gOBJ->transform.Rotation = glm::vec3(0, 0, 0);
    // child_gOBJ->transform.Scale = Scale;

    child_gOBJ->Parent = &Cam;
    Cam.Children.push_back(child_gOBJ);

    // Game loop
    while (!glfwWindowShouldClose(GameWindow.Context()))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        if(UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Update()){
            FAULT("GAME_INSTANCE::FAILED TO UPDATE!");
            //TODO: Call some sort of deinitializer (UnifiedEngine::Terminate())
            exit(10);
        }

        // gOBJ.transform.Rotation.x += 10 * Time.DeltaTime;
        // gOBJ.transform.Rotation.z += 10 * Time.DeltaTime;

        if(UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Render()){
            FAULT("GAME_INSTANCE::FAILED TO RENDER!");
            //TODO: Call some sort of deinitializer (UnifiedEngine::Terminate())
            exit(11);
        }

        //Temporary Tile Change TODO: Make this build into Window Class
        std::string title = "FPS: ";
        title += std::to_string((int)(1/UnifiedEngine::Time.DeltaTime));
        glfwSetWindowTitle(UnifiedEngine::__GAME__GLOBAL__INSTANCE__->__windows.front()->Context(), (title.c_str()));
    }

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();

    LOG("Program Terminated");
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
