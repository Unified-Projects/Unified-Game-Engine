#pragma once

//Includes
#include "../../Maths/Maths.h"
#include "../../Core/OpenGL/OpenGLInc.h"

#include <map>

//Font 
#include <freetype/freetype.h>
#include FT_FREETYPE_H

#include <iostream>

namespace UnifiedEngine {
    //Charecter Information
    struct Character {
        unsigned int TextureID;
        ivec2   Size;
        ivec2   Bearing;
        unsigned int Advance;
    };

    //Main Font
    class Font{
    private:
        //Library
        FT_Library ft;
        FT_Face face;
        
        //All Characters
        map<char, Character> Characters;
        
        //If Font Loaded or not
        bool FontLoaded;

        //File
        const char* OldFile;
        int OldFontSize;

        //Loading of the font
        bool LoadFont(){
            //Intialise Library
            if (FT_Init_FreeType(&this->ft))
            {
                return false;
            }

            //Initialise Face
            if (FT_New_Face(this->ft, this->File, 0, &this->face))
            {
                return false;
            }

            //Set Size Of Font
            FT_Set_Pixel_Sizes(this->face, 0, this->FontSize); 

            //Allignment
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            //ASCII
            for (unsigned char c = 0; c < 128; c++)
            {   
                //If Character exists
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                {
                    continue;
                }
                //Create a texture
                unsigned int texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);

                //Write Character to texture
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
                );

                //Texture config
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

                //Unbind
                glBindTexture(GL_TEXTURE_2D, 0);

                //Save character information
                Character character = {
                    texture,
                    ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x)
                };

                //Add character to map
                Characters.insert(pair<char, Character>(c, character));
            }
            //Main Unbind
            glBindTexture(GL_TEXTURE_2D, 0);

            //Free Library
            FT_Done_Face(this->face);
            FT_Done_FreeType(this->ft);
            return true;
        }

    public:
        //Public File and Size
        const char* File;
        int FontSize;

        //Init with default
        Font(){
            this->FontLoaded = false;
            this->FontSize = 11;
        }

        //Init Main
        Font(const char* FileLocation, int FontSize){
            this->FontLoaded = false;
            
            //File And Comparisons
            this->File = FileLocation;
            this->OldFile = this->File;

            this->FontSize = FontSize;
            this->OldFontSize = this->FontSize;

            //Returns True if Loaded Successfully
            this->FontLoaded = this->LoadFont();
        }

        //Free Memory (Need to revisit)
        ~Font(){
            /*for (const auto& [key, value] : this->Characters){
                GLuint id = value.TextureID;
                glDeleteTextures(1, &id);
            }*/
        }

        //Check Font file
        void UpdateFont(){
            if (this->File != this->OldFile && this->File != ""){
                this->FontLoaded = this->LoadFont();
                this->OldFile = this->File;
            }
                
            if (this->FontSize != this->OldFontSize && this->FontSize > 0 && this->File != ""){
                this->FontLoaded = this->LoadFont();
                this->OldFontSize = this->FontSize;
            }
        }

        //Get a character from font
        Character GetCharacter(int c){
            //If Exists return it
            if (this->FontLoaded){
                return this->Characters[c];
            }
            else{
                return Character{};
            }
        }
    };
}