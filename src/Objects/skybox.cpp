#include <Unified-Engine/Objects/skybox.h>
#include <Unified-Engine/includeGL.h>

using namespace UnifiedEngine;

Skybox::Skybox()
    : ObjectComponent(nullptr, OBJECT_SKYBOX)
{

}
Skybox::~Skybox(){

}

SkyboxSolidColor::SkyboxSolidColor(glm::vec3 Color){
    this->Color = glm::vec3(Color.x / 255, Color.y /255, Color.z / 255);
}
SkyboxSolidColor::~SkyboxSolidColor(){

}

int SkyboxSolidColor::Update(){
    //Nothing

    return 0;
}
int SkyboxSolidColor::Render(){
    //Render
    glClearColor(this->Color.x, this->Color.y, this->Color.z, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_STENCIL_BUFFER_BIT);

    return 0;
}