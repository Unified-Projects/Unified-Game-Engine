#pragma once

#include <GLM/vec2.hpp>
#include <Unified-Engine/includeGL.h>
#include <list>
#include <string>

namespace UnifiedEngine
{
    class Texture2D;

    struct TextureUVs{
        glm::vec2 UV[4];
    };

    struct Atlas_Space_Identifier
    {
        uint32_t x;
        uint32_t y;
        uint32_t w;
        uint32_t h;
    };

    struct Atlas_Texture_Identifier
    {
        uint32_t x;
        uint32_t y;
        uint32_t w;
        uint32_t h;
        Texture2D* Texture;
    };

    struct Atlas_Image_Location
    {
        glm::ivec2 pos;
        GLuint Dest;
        int index;
    };
    
    class TextureAtlas{
        friend Texture2D;
    protected:
        std::list<GLuint> TextureIdentifiers;

        std::list<std::list<Atlas_Space_Identifier>> SpaceIdentifiers;
        std::list<std::list<Atlas_Texture_Identifier>> Texture2DIdentifiers;

        GLuint Bound = 0;

    protected:
        Atlas_Image_Location FindAvailableSpace(glm::ivec2 size);
        int CopyImageData(GLuint Dest, GLuint Src, glm::ivec2 Position, glm::ivec2 Size);
        int CopyImageData(GLuint Dest, uint8_t* Src, glm::ivec2 Position, glm::ivec2 Size);
        GLuint CreateNewImage();
    
    public:
        TextureAtlas();
        ~TextureAtlas();

    public:
        int AddImage(Texture2D* image);
        int RemoveImage(Texture2D* image);

        int Toggle(Texture2D* image);
    };

    //TODO: if no atlas return faults on attempts to load texture
    extern TextureAtlas* __GLOBAL_ATLAS;

    class Texture2D{
        friend TextureAtlas;
    protected:
        std::string FilePath;
        uint8_t* Data;

        int width;
        int height;

    public:
        TextureUVs UVs;
        const TextureUVs& UVsr; // TODO MOVE TO PROTECTED
        const GLuint& TextID;
        GLuint TextureID;

    public:
        Texture2D(std::string FilePath);
        Texture2D(uint8_t* Data, int width, int height);
        ~Texture2D();

    public:
        int UpdateTeture(std::string FilePath);
        int UpdateTeture(uint8_t* Data, int width, int height);

        int Bind();
        int Unbind();

    public: //Operators
        //Allow conversion from atlas to a texture (Import to the global Atlas)
        void operator=(TextureAtlas* Atlas);
    };

} // namespace UnifiedEngine
