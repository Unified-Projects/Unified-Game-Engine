#include <Unified-Engine/Objects/Components/material.h>
#include <Unified-Engine/debug.h>
#include <Unified-Engine/Objects/Components/shaderObject.h>

using namespace UnifiedEngine;

Material::Material(ObjectComponent* Parent)
    : ObjectComponent(Parent, OBJECT_MATERIAL)
{
    if(Parent->type != OBJECT_SHADER_OBJECT){
        FAULT("PARENT NEEDS TO BE SHADER_OBJECT");
        return;
    }
}
Material::~Material(){

}

int Material::Update(){
    return 0;
}
int Material::Render(){
    return 0;
}

ColorMaterial::ColorMaterial(ObjectComponent* Parent)
    : Material(Parent)
{
    if(Parent->type != OBJECT_SHADER_OBJECT){
        FAULT("PARENT NEEDS TO BE SHADER_OBJECT");
        return;
    }
}
ColorMaterial::~ColorMaterial(){

}

int ColorMaterial::Update(){
    return 0;
}
int ColorMaterial::Render(){
    return 0;
}

GradientMaterial::GradientMaterial(ObjectComponent* Parent)
    : Material(Parent)
{
    if(Parent->type != OBJECT_SHADER_OBJECT){
        FAULT("PARENT NEEDS TO BE SHADER_OBJECT");
        return;
    }
}
GradientMaterial::~GradientMaterial(){

}

int GradientMaterial::Update(){
    return 0;
}
int GradientMaterial::Render(){
    return 0;
}

Texture2DMaterial::Texture2DMaterial(ObjectComponent* Parent, Texture2D* texture)
    : Material(Parent)
{
    if(Parent->type != OBJECT_SHADER_OBJECT){
        FAULT("PARENT NEEDS TO BE SHADER_OBJECT");
        return;
    }

    this->texture = texture;

    //Create Args For Parent
    ShaderObject* parentShader = (ShaderObject*)Parent;

    ShaderArguments TextureArg = {.dataLoc = (unsigned int*)(&(this->texture->TextureID)), .type = SHADER_ARG_INT, .name = "Texture"};
    // ShaderArguments UVArg = {.dataLoc = &this->texture->UVsr.UV, .type = SHADER_ARG_VEC2, .name = "UVMap"};
    ShaderArguments UVArg0 = {.dataLoc = &(this->texture->UVs.UV[0]), .type = SHADER_ARG_VEC2, .name = "UVMap[0]"};
    ShaderArguments UVArg1 = {.dataLoc = &(this->texture->UVs.UV[1]), .type = SHADER_ARG_VEC2, .name = "UVMap[1]"};
    ShaderArguments UVArg2 = {.dataLoc = &(this->texture->UVs.UV[2]), .type = SHADER_ARG_VEC2, .name = "UVMap[2]"};
    ShaderArguments UVArg3 = {.dataLoc = &(this->texture->UVs.UV[3]), .type = SHADER_ARG_VEC2, .name = "UVMap[3]"};

    parentShader->Arguments.push_back(TextureArg);
    parentShader->Arguments.push_back(UVArg0);
    parentShader->Arguments.push_back(UVArg1);
    parentShader->Arguments.push_back(UVArg2);
    parentShader->Arguments.push_back(UVArg3);
}
Texture2DMaterial::~Texture2DMaterial(){
    //TODO: Remove arguments from Shader
}

int Texture2DMaterial::Update(){ //TODO: Make it update the arguments to set texture to the correct ID and UVs incase of change
    this->texture->Bind();
    return 0;
}
int Texture2DMaterial::Render(){
    return 0;
}