#include <Unified-Engine/Objects/Components/texture2d.h>
#include <Unified-Engine/debug.h>
#include <vector>
#include <SOIL2/SOIL2.h>
#include <iostream>
#include <cstdint>
#include <cstring>

using namespace UnifiedEngine;

TextureAtlas* UnifiedEngine::__GLOBAL_ATLAS = nullptr;

// protected:
// std::list<GLuint> TextureIdentifiers;
// std::list<glm::ivec2>  Size; //Now fixed to 4096x4096

// std::vector<std::vector<Atlas_Space_Identifier>> SpaceIdentifiers;
// std::vector<std::vector<Atlas_Texture_Identifier>> Texture2DIdentifiers;

Atlas_Image_Location TextureAtlas::FindAvailableSpace(glm::ivec2 Size){

    int index = 0;

    for (auto i = this->SpaceIdentifiers.begin(); i != this->SpaceIdentifiers.end(); i++){
        for (auto j = (*i).begin(); j != (*i).end(); j++){
            if(Size.x <= (*j).w && Size.y <= (*j).h){
                Atlas_Space_Identifier Small = {};
                Atlas_Space_Identifier Big = {};

                Small.x = (*j).x + Size.x;
                Small.y = (*j).y;
                Small.w = (*j).w - Size.x;
                Small.h = Size.y;

                Big.x = (*j).x;
                Big.y = (*j).y + Size.y;
                Big.w = (*j).w;
                Big.h = (*j).h - Size.y;

                if(Big.w || Big.h)
                    (*i).insert(j, Big);
                if(Small.w || Small.h)
                    (*i).insert(j, Small);

                (*i).erase((j));

                return Atlas_Image_Location{glm::ivec2(Big.x, Small.y), (*(std::next(this->TextureIdentifiers.begin(), index))), index};
            }
        }

        index++;
    }

    return Atlas_Image_Location{glm::ivec2(-1), 0};
}
int TextureAtlas::CopyImageData(GLuint Dest, GLuint Src, glm::ivec2 Position, glm::ivec2 Size){

    /*

    unsigned char * sourceData = (unsigned char *)malloc(sourceTextWidth * sourceTextHeight * formatOffset);

    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, sourceData);

    glBindTexture( GL_TEXTURE_2D, m_currentTextureId );

    unsigned char * destData = (unsigned char *)malloc(width * height * 3);



    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, sourceData);

    for (int i = 0; i < height; ++i)
    {       
    memcpy(&destData[(i * width * 3) ], &sourceData[((i + y) * sourceTextWidth * 3) + (x * 3)], width * 3);
    }
    //glDeleteTextures (1, m_currentTextureId);
    glBindTexture( GL_TEXTURE_2D, m_currentTextureId );

    glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB,GL_UNSIGNED_BYTE, destData );
    free(destData);
    free(sourceData);

    */

    return 0;
}
int TextureAtlas::CopyImageData(GLuint Dest, uint8_t* Src, glm::ivec2 Position, glm::ivec2 Size){

    glBindTexture(GL_TEXTURE_2D, Dest);

    //Get the data
    unsigned char * destData = (unsigned char *)malloc(4096 * 4096 * 4);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, destData);

    for(int i = Position.y; i < Position.y + Size.y; i++){
        std::memcpy(destData + (i * 4096 * 4) + (Position.x * 4), Src + (Size.x * (i - Position.y) * 4), (Size.x * 4));
    }

    // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 4096, 4096, GL_BGRA, GL_UNSIGNED_BYTE, destData);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4096, 4096, 0, GL_RGBA, GL_UNSIGNED_BYTE, destData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    this->Bound = 0;

    return 0;
}
GLuint TextureAtlas::CreateNewImage(){

    std::vector<GLubyte> emptyData(4096 * 4096 * 4, 0);
    GLuint id;
    glGenTextures(1, &id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, id);
    // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 4096, 4096, GL_BGRA, GL_UNSIGNED_BYTE, &emptyData[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4096, 4096, 0, GL_RGBA, GL_UNSIGNED_BYTE, &emptyData[0]);

    glGenerateMipmap(GL_TEXTURE_2D);

    return id;
}

TextureAtlas::TextureAtlas(){
    //Initialise Lists
    this->TextureIdentifiers = {};
    this->SpaceIdentifiers = {};
    this->Texture2DIdentifiers = {};

    //Create First Texture Space
    GLuint id = CreateNewImage();

    //Load the texture info
    this->TextureIdentifiers.push_back(id);
    this->SpaceIdentifiers.push_back(std::list<Atlas_Space_Identifier>{Atlas_Space_Identifier{0, 0, 4096, 4096}});
    this->Texture2DIdentifiers.push_back(std::list<Atlas_Texture_Identifier>{});
}
TextureAtlas::~TextureAtlas(){
    for (auto i = this->TextureIdentifiers.begin(); i != this->TextureIdentifiers.end(); i++){
        glDeleteTextures(1, &(*i));
    }
}

int TextureAtlas::AddImage(Texture2D* image){
    //First Check it fits
    Atlas_Image_Location position = this->FindAvailableSpace(glm::ivec2(image->width, image->height));

    if(position.Dest == 0){
        FAULT("COULD NOT FIT IMAGE");
        return -1;
    }

    this->CopyImageData(position.Dest, image->Data, position.pos, glm::ivec2(image->width, image->height));

    (*(std::next(this->Texture2DIdentifiers.begin(), position.index))).push_back(Atlas_Texture_Identifier{(uint32_t)position.pos.x, (uint32_t)position.pos.y, (uint32_t)image->width, (uint32_t)image->height, image});

    image->UVs.UV[0] = glm::vec2((position.pos.x) / 4096.0f, 1.f - ((position.pos.y) / 4096.0f)); //0,1
    image->UVs.UV[1] = glm::vec2((position.pos.x + image->width) / 4096.0f, 1.f - ((position.pos.y) / 4096.0f)); //1, 1
    image->UVs.UV[2] = glm::vec2((position.pos.x) / 4096.0f, 1.f - ((position.pos.y + image->height) / 4096.0f)); //0, 0
    image->UVs.UV[3] = glm::vec2((position.pos.x + image->width) / 4096.0f, 1.f - ((position.pos.y + image->height) / 4096.0f)); //1, 0

    image->TextureID = position.Dest;

    return 0;
}
int TextureAtlas::RemoveImage(Texture2D* image){
    FAULT("NOT IMPLEMENTED YET");
    return 0;
}

int TextureAtlas::Toggle(Texture2D* image){
    int index = 0;
    for (auto i = this->Texture2DIdentifiers.begin(); i != this->Texture2DIdentifiers.end(); i++){
        for (auto j = (*i).begin(); j != (*i).end(); j++){
            if((*j).Texture == image){
                glBindTexture(GL_TEXTURE_2D, 0);
                glActiveTexture(0);

                this->Bound = (*(std::next(this->TextureIdentifiers.begin(), index)));
                glBindTexture(GL_TEXTURE_2D, this->Bound);
                glActiveTexture(GL_TEXTURE0 + this->Bound);
                return 0;
            }
        }

        index++;
    }

    return 0;
}

Texture2D::Texture2D(std::string FilePath)
    : UVsr(UVs), TextID(TextureID)
{
    if(!__GLOBAL_ATLAS){
        FAULT("ERROR NO ATLAS");
        return;
    }

    this->FilePath = FilePath;

    this->Data = SOIL_load_image(this->FilePath.c_str(), &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

    if(!Data){
        FAULT("COULD NOT AQUIRE DATA");
        return;
    }

    __GLOBAL_ATLAS->AddImage(this);

    SOIL_free_image_data(this->Data);
}
Texture2D::Texture2D(uint8_t* Data, int width, int height)
    : UVsr(UVs), TextID(TextureID)
{
    if(!__GLOBAL_ATLAS){
        FAULT("ERROR NO ATLAS");
        return;
    }

    if(!Data){
        FAULT("COULD NOT AQUIRE DATA");
        return;
    }

    this->Data = Data;
    this->width = width;
    this->height = height;

    __GLOBAL_ATLAS->AddImage(this);
}
Texture2D::~Texture2D(){
    if(!__GLOBAL_ATLAS){
        FAULT("ERROR NO ATLAS");
        return;
    }

    __GLOBAL_ATLAS->RemoveImage(this);
}

int Texture2D::UpdateTeture(std::string FilePath){

    if(!__GLOBAL_ATLAS){
        FAULT("ERROR NO ATLAS");
        return -1;
    }

    __GLOBAL_ATLAS->RemoveImage(this);

    this->FilePath = FilePath;
    this->Data = SOIL_load_image(this->FilePath.c_str(), &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

    if(!Data){
        FAULT("COULD NOT AQUIRE DATA");
        return -1;
    }

    __GLOBAL_ATLAS->AddImage(this);

    SOIL_free_image_data(this->Data);

    return 0;
}
int Texture2D::UpdateTeture(uint8_t* Data, int width, int height){
    if(!__GLOBAL_ATLAS){
        FAULT("ERROR NO ATLAS");
        return -1;
    }

    if(!Data){
        FAULT("COULD NOT AQUIRE DATA");
        return -1;
    }

    __GLOBAL_ATLAS->RemoveImage(this);

    this->Data = Data;
    this->width = width;
    this->height = height;

    __GLOBAL_ATLAS->AddImage(this);


    return 0;
}

int Texture2D::Bind(){
    if(!__GLOBAL_ATLAS){
        FAULT("ERROR NO ATLAS");
        return -1;
    }

    __GLOBAL_ATLAS->Toggle(this);

    return 0;
}
int Texture2D::Unbind(){
    if(!__GLOBAL_ATLAS){
        FAULT("ERROR NO ATLAS");
        return -1;
    }

    return 0;
}


//Allow conversion from atlas to a texture (Import to the global Atlas)
void Texture2D::operator=(TextureAtlas* Atlas){
    FAULT("NOT IMPLEMENTED YET");
}