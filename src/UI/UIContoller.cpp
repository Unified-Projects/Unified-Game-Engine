#include <Unified-Engine/UI/UIContoller.h>

using namespace UnifiedEngine;
using namespace UnifiedEngine::UI;

GUI::GUI(UnifiedEngine::Window* RenderWindow){
    // Setup Shader Objects
    this->ShaderElement = new Shader("UI", "UI"); // LOADS STANDARD UI

    this->RenderWindow = RenderWindow;

    // Setup root Panel
    this->RootWindow = new Panel(nullptr, {}, {-1, -1}, {2, 2}, {0, 0, 1, 1});
}
GUI::~GUI(){

}

int GUI::Update(){
    this->RootWindow->Update(this);
    return 0;
}
int GUI::Render(){
    this->RootWindow->Render(this);
    return 0 ;
}