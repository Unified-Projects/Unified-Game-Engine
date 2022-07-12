#include <iostream>

#include <Unified-Engine/debug.h>
#include <Unified-Engine/core/instance.h>
#include <Unified-Engine/Core/Rendering/shader.h>
#include <Unified-Engine/Objects/gameObject.h>
#include <Unified-Engine/Objects/Mesh/Defaults/cube.h>

#include <cstdlib>

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The MAIN function, from here we start the application and run the game loop
int main()
{
    // UnifiedEngine::__GLOBAL_CONFIG__.VersionMajor = 4;
    // UnifiedEngine::__GLOBAL_CONFIG__.VersionMinor = 6;

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

    UnifiedEngine::WindowConfig WinConf = {1260, 720, 0, 0, "Test Program", true, false, true};
    WinConf.backgroundColor = {0, 0, 0};

    UnifiedEngine::Window GameWindow(WinConf);

    // Set the required callback functions
    glfwSetKeyCallback(GameWindow.Context(), key_callback);

    UnifiedEngine::Shader shader("../rsc/testVertex.glsl", "../rsc/testFragment.glsl");
    UnifiedEngine::ShaderObject shaderObj(&shader);

    glm::vec4 col = {1, 1, 1, 1};
    shaderObj.Arguments.push_back(UnifiedEngine::ShaderArguments{(void*)(&col), UnifiedEngine::SHADER_ARG_VEC4, "incol"});

    UnifiedEngine::Mesh mesh;
    // mesh.vertices = {
    //     UnifiedEngine::Vertex{.position=glm::vec3(-0.9f, -0.5f, 0.0f)},
    //     UnifiedEngine::Vertex{.position=glm::vec3(-0.0f, -0.5f, 0.0f)},
    //     UnifiedEngine::Vertex{.position=glm::vec3(-0.45f, 0.5f, 0.0f)},

    //     UnifiedEngine::Vertex{.position=glm::vec3(0.0f, -0.5f, 0.0f)},
    //     UnifiedEngine::Vertex{.position=glm::vec3(0.9f, -0.5f, 0.0f)},
    //     UnifiedEngine::Vertex{.position=glm::vec3(0.45f, 0.5f, 0.0f)}
    // };

    glm::vec3 color1(1, 1, 1);
	glm::vec3 color2(0, 1, 1);
	glm::vec3 color3(1, 0, 1);
	glm::vec3 color4(1, 1, 0);
	glm::vec3 color5(0, 0, 1);
	glm::vec3 color6(1, 0, 0);

    std::vector<UnifiedEngine::Vertex> vertices = {
		//Position                               //Color        //Texcoords                   //Normals
		 //Front
		 UnifiedEngine::Vertex{glm::vec3(-.5f, .5f, .5f),       color1,        glm::vec2(0, 1),              glm::vec3(0.f, 0.f, -1.f)},
		 UnifiedEngine::Vertex{glm::vec3(-.5f, -.5f, .5f),      color1,        glm::vec2(0, 0),              glm::vec3(0.f, 0.f, -1.f)},
		 UnifiedEngine::Vertex{glm::vec3(.5f, -.5f, .5f),       color1,        glm::vec2(1, 0),              glm::vec3(0.f, 0.f, -1.f)},
		 UnifiedEngine::Vertex{glm::vec3(.5f, .5f, .5f),        color1,        glm::vec2(1, 1),              glm::vec3(0.f, 0.f, -1.f)},

		 //Back
		 UnifiedEngine::Vertex{glm::vec3(-.5f, .5f, -.5f),      color2,        glm::vec2(0, 1),              glm::vec3(0.f, 0.f, 1.f)},
		 UnifiedEngine::Vertex{glm::vec3(-.5f, -.5f, -.5f),     color2,        glm::vec2(0, 0),              glm::vec3(0.f, 0.f, 1.f)},
		 UnifiedEngine::Vertex{glm::vec3(.5f, -.5f, -.5f),      color2,        glm::vec2(1, 0),              glm::vec3(0.f, 0.f, 1.f)},
		 UnifiedEngine::Vertex{glm::vec3(.5f, .5f, -.5f),       color2,        glm::vec2(1, 1),              glm::vec3(0.f, 0.f, 1.f)},

		 //Left
		 UnifiedEngine::Vertex{glm::vec3(-.5f, .5f, -.5f),      color3,        glm::vec2(0, 1),              glm::vec3(1.f, 0.f, 0.f)},
		 UnifiedEngine::Vertex{glm::vec3(-.5f, -.5f, -.5f),     color3,        glm::vec2(0, 0),              glm::vec3(1.f, 0.f, 0.f)},
		 UnifiedEngine::Vertex{glm::vec3(-.5f, -.5f, .5f),      color3,        glm::vec2(1, 0),              glm::vec3(1.f, 0.f, 0.f)},
		 UnifiedEngine::Vertex{glm::vec3(-.5f, .5f, .5f),       color3,        glm::vec2(1, 1),              glm::vec3(1.f, 0.f, 0.f)},

		 //Right
		 UnifiedEngine::Vertex{glm::vec3(.5f, .5f, -.5f),       color4,        glm::vec2(0, 1),              glm::vec3(-1.f, 0.f, 0.f)},
		 UnifiedEngine::Vertex{glm::vec3(.5f, -.5f, -.5f),      color4,        glm::vec2(0, 0),              glm::vec3(-1.f, 0.f, 0.f)},
		 UnifiedEngine::Vertex{glm::vec3(.5f, -.5f, .5f),       color4,        glm::vec2(1, 0),              glm::vec3(-1.f, 0.f, 0.f)},
		 UnifiedEngine::Vertex{glm::vec3(.5f, .5f, .5f),        color4,        glm::vec2(1, 1),              glm::vec3(-1.f, 0.f, 0.f)},

		 //Top
		 UnifiedEngine::Vertex{glm::vec3(-.5f, .5f, -.5f),      color5,        glm::vec2(0, 1),              glm::vec3(0.f, -1.f, 0.f)},
		 UnifiedEngine::Vertex{glm::vec3(-.5f, .5f, .5f),       color5,        glm::vec2(0, 0),              glm::vec3(0.f, -1.f, 0.f)},
		 UnifiedEngine::Vertex{glm::vec3(.5f, .5f, .5f),        color5,        glm::vec2(1, 0),              glm::vec3(0.f, -1.f, 0.f)},
		 UnifiedEngine::Vertex{glm::vec3(.5f, .5f, -.5f),       color5,        glm::vec2(1, 1),              glm::vec3(0.f, -1.f, 0.f)},

		 //bottom
		 UnifiedEngine::Vertex{glm::vec3(-.5f, -.5f, -.5f),     color6,        glm::vec2(0, 1),              glm::vec3(0.f, 1.f, 0.f)},
		 UnifiedEngine::Vertex{glm::vec3(-.5f, -.5f, .5f),      color6,        glm::vec2(0, 0),              glm::vec3(0.f, 1.f, 0.f)},
		 UnifiedEngine::Vertex{glm::vec3(.5f, -.5f, .5f),       color6,        glm::vec2(1, 0),              glm::vec3(0.f, 1.f, 0.f)},
		 UnifiedEngine::Vertex{glm::vec3(.5f, -.5f, -.5f),      color6,        glm::vec2(1, 1),              glm::vec3(0.f, 1.f, 0.f)}
	};

	//Indices
	std::vector<GLuint> indicies = {
		// 0, 1, 2,
		// 0, 2, 3,

		// 6, 5, 4,
		// 7, 6, 4,

		// 8, 9, 10,
		// 8, 10, 11,

		// 14, 13, 12,
		// 15, 14, 12,

		// 16, 17, 18,
		// 16, 18, 19,

		// 22, 21, 20,
		// 23, 22, 20
		2, 1, 0,
		3, 2, 0,

		4, 5, 6,
		4, 6, 7,

		10, 9, 8,
		11, 10, 8,

		12, 13, 14,
		12, 14, 15,

		18, 17, 16,
		19, 18, 16,

		20, 21, 22,
		20, 22, 23
	};

    //Mesh
    mesh.vertices = vertices;
    mesh.indices = indicies;

    // mesh = UnifiedEngine::Cube();

    UnifiedEngine::GameObject gOBJ(mesh, &shaderObj);
    gOBJ.transform.Position.z += 10;
    UnifiedEngine::instantiate(&gOBJ);

    UnifiedEngine::GameObject gOBJ1(mesh, &shaderObj);
    gOBJ.transform.Position.z -= 10;
    UnifiedEngine::instantiate(&gOBJ1);

    UnifiedEngine::GameObject gOBJ2(mesh, &shaderObj);
    gOBJ.transform.Position.x += 10;
    UnifiedEngine::instantiate(&gOBJ2);

    UnifiedEngine::GameObject gOBJ3(mesh, &shaderObj);
    gOBJ.transform.Position.x -= 10;
    UnifiedEngine::instantiate(&gOBJ3);

    UnifiedEngine::GameObject gOBJ4(mesh, &shaderObj);
    gOBJ.transform.Position.y += 10;
    UnifiedEngine::instantiate(&gOBJ4);

    UnifiedEngine::GameObject gOBJ5(mesh, &shaderObj);
    gOBJ.transform.Position.y -= 10;
    UnifiedEngine::instantiate(&gOBJ5);

    //Camera
    UnifiedEngine::Camera Cam;
    // Cam.Position = {0.f, 0.f, 0.f};
    UnifiedEngine::__GAME__GLOBAL__INSTANCE__->camera = &Cam;

    // Game loop
    while (!glfwWindowShouldClose(GameWindow.Context()))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        if(UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Update()){
            FAULT("GAME_INSTANCE::FAILED TO UPDATE!");
            //TODO: Call some sort of deinitializer (UnifiedEngine::Terminate())
            exit(10);
        }

        if(UnifiedEngine::__GAME__GLOBAL__INSTANCE__->Render()){
            FAULT("GAME_INSTANCE::FAILED TO RENDER!");
            //TODO: Call some sort of deinitializer (UnifiedEngine::Terminate())
            exit(11);
        }
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