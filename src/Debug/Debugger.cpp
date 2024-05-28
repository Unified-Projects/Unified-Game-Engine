#include <Unified-Engine/Debug/Debugger.h>

#include <Unified-Engine/includeGL.h>

using namespace UnifiedEngine::Debug;

DebugWindow::DebugWindow(WindowConfig config){
    this->Config = config; // Save
    this->window = new Window(config); // Create window

    this->GUIInt = new UI::GUI(this->window);

    // Split into 3 panels
    this->GUIInt->RootWindow->children.push_back(new UI::Panel(this->GUIInt->RootWindow, {}, {-1,0}, {2/3, 2}, {1, 0, 0, 1}));
    this->GUIInt->RootWindow->children.push_back(new UI::Panel(this->GUIInt->RootWindow, {}, {-1/3, 0}, {2/3, 2}, {1, 1, 0, 1}));
    this->GUIInt->RootWindow->children.push_back(new UI::Panel(this->GUIInt->RootWindow, {}, {1/3, 0}, {2/3, 2}, {1, 1, 1, 1}));
}

DebugWindow::~DebugWindow(){
    
}

int DebugWindow::Update(){
    GUIInt->Update();
    return 0;
}

int DebugWindow::Render(){
    // Window Context
    this->window->Activate();

    if(this->Framebuffer)
        glDeleteFramebuffers(1, &this->Framebuffer);
    if(this->Renderbuffer)
        glDeleteRenderbuffers(1, &this->Renderbuffer);
    if(this->Texture)
        glDeleteTextures(1, &this->Texture);

    //
    // Resolution Stuff
    //
    {
        glViewport(0, 0, this->window->Config().res_x,  this->window->Config().res_y);

        glGenFramebuffers(1, &this->Framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, this->Framebuffer);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    //
    // Resolution Stuff
    //
    {
        glGenTextures(1, &this->Texture);
        glBindTexture(GL_TEXTURE_2D, this->Texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->window->Config().res_x, this->window->Config().res_y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        
        glGenRenderbuffers(1, &this->Renderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, this->Renderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, this->window->Config().res_x, this->window->Config().res_y);
        
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->Texture, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->Renderbuffer);
    }

    // Render
    // Clear the colorbuffer
    glClearColor(this->window->Config().backgroundColor.red, this->window->Config().backgroundColor.green, this->window->Config().backgroundColor.blue, this->window->Config().backgroundColor.alpha);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_STENCIL_BUFFER_BIT);
    
    //Draw Objects
    GUIInt->Render();

    //
    // Resolution Stuff
    //
    {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT); //If issues dissable me
        // glClear(GL_STENCIL_BUFFER_BIT);

        glViewport(0, 0, this->window->Config().x,  this->window->Config().y);

        glBlitFramebuffer(0, 0, this->window->Config().res_x, this->window->Config().res_y, 0, 0, this->window->Config().x, this->window->Config().y, GL_COLOR_BUFFER_BIT, GL_NEAREST);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    // Swap the screen buffers
    if (this->window->Config().vsync) {
        glfwSwapBuffers(this->window->Context());
    }

    return 0;
}