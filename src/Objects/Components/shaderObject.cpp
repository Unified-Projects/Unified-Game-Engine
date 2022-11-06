#include <Unified-Engine/Objects/Components/shaderObject.h>
#include <Unified-Engine/Objects/gameObject.h>
#include <Unified-Engine/debug.h>
#include <Unified-Engine/Core/instance.h>

using namespace UnifiedEngine;

ShaderObject::ShaderObject(Shader* shaderRef)
    : ObjectComponent(nullptr, OBJECT_SHADER_OBJECT)
{
    this->shader = shaderRef;
}

ShaderObject::~ShaderObject(){

}


int ShaderObject::Toggle(){
    if (this->Toggled){
        this->shader->unbind();
    }
    else{
        this->shader->use();
    }

    this->Toggled = !this->Toggled;

    return 0;
}

int SendArg(Shader* shader, ShaderArguments arg){
    switch (arg.type)
    {
    case SHADER_ARG_INT:
        shader->set1i(*((int*)arg.dataLoc), arg.name.c_str());
        return 0;
    case SHADER_ARG_FLOAT:
        shader->set1f(*((float*)arg.dataLoc), arg.name.c_str());
        return 0;
    case SHADER_ARG_VEC2:
        shader->setVec2f(*((glm::vec2*)arg.dataLoc), arg.name.c_str());
        return 0;
    case SHADER_ARG_VEC3:
        shader->setVec3f(*((glm::vec3*)arg.dataLoc), arg.name.c_str());
        return 0;
    case SHADER_ARG_VEC4:
        shader->setVec4f(*((glm::vec4*)arg.dataLoc), arg.name.c_str());
        return 0;
    case SHADER_ARG_MAT3:
        shader->setMat3fv(*((glm::mat3*)arg.dataLoc), arg.name.c_str());
        return 0;
    case SHADER_ARG_MAT4:
        shader->setMat4fv(*((glm::mat4*)arg.dataLoc), arg.name.c_str());
        return 0;
    
    default:
        return -1;
    }

    return 0;
}

int ShaderObject::PassArgs(){

    for (auto i = this->Children.begin(); i != this->Children.end(); i++) {
        if((*i)->type == OBJECT_MATERIAL){
            (*i)->Update();
        }
    }

    for (auto i = this->Arguments.begin(); i != this->Arguments.end(); i++) {
        ShaderArguments arg = (*i);

        if(SendArg(this->shader, arg)){
            FAULT("FAILED TO PARSE ARGUMENT");
            return -1;
        }
    }

    //TODO: Send Shader specifics
    if(Parent->type != OBJECT_GAME_OBJECT){
        FAULT("Cannot read non-gameobject");
        return -1;
    }else if(__GAME__GLOBAL__INSTANCE__->GetMainCamera() == nullptr){
        FAULT("Cannot read from camera object. Is it present?");
        return -1;
    }else if(__GAME__GLOBAL__INSTANCE__->__windows.size() == 0){
        FAULT("Cannot read from window object. Is it present?");
        return -1;
    }

    GameObject* ParentObj = (GameObject*)Parent;

    //Matricies
    SendArg(this->shader, {.dataLoc=&(ParentObj->ModelMatrix), .type=SHADER_ARG_MAT4, .name="ModelMatrix"});
    SendArg(this->shader, {.dataLoc=&(__GAME__GLOBAL__INSTANCE__->GetMainCamera()->ViewMatrix), .type=SHADER_ARG_MAT4, .name="ViewMatrix"});
    SendArg(this->shader, {.dataLoc=&(__GAME__GLOBAL__INSTANCE__->ProjectionMatrix), .type=SHADER_ARG_MAT4, .name="ProjectionMatrix"});

    //GameObject
    SendArg(this->shader, {.dataLoc=&(ParentObj->transform.Position), .type=SHADER_ARG_VEC3, .name="ObjectPosition"});
    SendArg(this->shader, {.dataLoc=&(ParentObj->transform.Rotation), .type=SHADER_ARG_VEC3, .name="ObjectRotation"});

    //Camera
    SendArg(this->shader, {.dataLoc=&(__GAME__GLOBAL__INSTANCE__->GetMainCamera()->transform.Position), .type=SHADER_ARG_VEC3, .name="CameraPosition"});
    SendArg(this->shader, {.dataLoc=&(__GAME__GLOBAL__INSTANCE__->GetMainCamera()->transform.Rotation), .type=SHADER_ARG_VEC3, .name="CameraRotation"});
    SendArg(this->shader, {.dataLoc=&(__GAME__GLOBAL__INSTANCE__->GetMainCamera()->ViewFront), .type=SHADER_ARG_VEC3, .name="CameraFront"});

    return 0;
}
