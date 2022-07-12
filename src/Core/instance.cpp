#include <Unified-Engine/Core/instance.h>
#include <Unified-Engine/debug.h>

using namespace UnifiedEngine;

namespace UnifiedEngine
{
    GameInstance* __GAME__GLOBAL__INSTANCE__ = nullptr;

    /**
     * @brief Creates a main game engine instance
     * 
     * @return int (-1 for error)
     */
    int __INIT__ENGINE(){
        if(__GAME__GLOBAL__INSTANCE__){
            WARN("ATTEMPTED TO RE-INITIALISE");
            return -1;
        }

        __GAME__GLOBAL__INSTANCE__ = new GameInstance();

        return 0;
    }

    //Enable
	void OpenGLEnable(GLenum ToEnable) {
		glEnable(ToEnable);
	}

	//Disable
	void OpenGLDisable(GLenum ToDisable) {
		glEnable(ToDisable);
	}

	//PolygonMode
	void OpenGLPolygonMode(GLenum Face, GLenum Mode) {
		glPolygonMode(Face, Mode);
	}

	//Blending
	void OpenGLBlend(GLenum SFactor, GLenum DFactor) {
		glBlendFunc(SFactor, DFactor);
	}

	//GLRendering
	void OpenGLRendering(GLenum Cull, GLenum Front) {
		glCullFace(Cull);
		glFrontFace(Front);
	}

    GameInstance::GameInstance(){
        // Init GLFW
        glfwInit();

        // Set all the required options for GLFW
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
    GameInstance::~GameInstance(){

    }

    int GameInstance::_Init_Glad(){
        //Load and check if Glad is loaded
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            FAULT("Failed to initialize GLAD");
            return -1;
        }

        gladInited = true;

        //Configure
        OpenGLEnable(GL_DEPTH_TEST);
        OpenGLEnable(GL_CULL_FACE);
        OpenGLRendering(GL_BACK, GL_CCW);
        OpenGLEnable(GL_BLEND);
        OpenGLBlend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        OpenGLPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        return 0;
    }

    /**
     * @brief Update and call component updates
     * 
     * @return int 
     */
    int GameInstance::Update(){
        if(!this->__windows.size()){
            FAULT("No Window Object Located");
            return -1;
        }

        if(!this->camera){
            FAULT("No Camera Object Located");
            return -1;
        }

        //First Update Input
        glfwPollEvents();

        for (auto i = this->objects.begin(); i != this->objects.end(); i++) {
            (*i)->Update();
        }

        //Camera
        this->camera->Update();
        this->ProjectionMatrix = glm::mat4(1.f);
        this->ProjectionMatrix = glm::perspective(glm::radians(this->camera->FOV), static_cast<float>(this->__windows.front()->Config().res_x) / this->__windows.front()->Config().res_y, this->camera->NearPlane, this->camera->FarPlane);

        return 0;
    }

    /**
     * @brief Draws All Objects to the screen
     * 
     * @return int 
     */
    int GameInstance::Render(){
        if(!this->__windows.size()){
            FAULT("No Window Object Located");
            return -1;
        }

        if(!this->camera){
            FAULT("No Camera Object Located");
            return -1;
        }

        OpenGLEnable(GL_DEPTH_TEST);

        // Render
        // Clear the colorbuffer
        glClearColor(this->__windows.front()->Config().backgroundColor.red, this->__windows.front()->Config().backgroundColor.green, this->__windows.front()->Config().backgroundColor.blue, this->__windows.front()->Config().backgroundColor.alpha);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_STENCIL_BUFFER_BIT);

        //Draw Objects
        for (auto i = this->objects.begin(); i != this->objects.end(); i++) {
            (*i)->Render();
        }

        // Swap the screen buffers
        glfwSwapBuffers(this->__windows.front()->Context());
        return 0;
    }

} // namespace UnifiedEngine