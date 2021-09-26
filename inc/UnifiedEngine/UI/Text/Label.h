#pragma once

//Includes
#include "../../Maths/Maths.h"
#include "../../Core/Renderer/Shader.h"
#include "../../Core/Renderer/RenderInfo.h"
#include "Font.h"
#include "../../Object/Components/Resources.h"

#include <string>

namespace UnifiedEngine {
    //Label Class
    class Label{
    private:
        //Buffers
        GLuint VAO;
        GLuint VBO;

        //Renderer
        Shader shader;

        //Scaling with screen size
        bool UpdateScale = false;
        vec2 NewScale;
    public:
        //UI Looks
        string Text;
        Font font;
        
        //UI Render Stuff
        vec2 Position;
        vec2 Scale;
        vec3 Color;

        //Locators
        string Name;
        string Tag;

        bool Active;
        
        //Texture
        Texture2D* texture;

        //Init with font
        Label(Font font)
            : shader("./rsc/DefaultShaders/UI/vertex_text.glsl", "./rsc/DefaultShaders/UI/fragment_text.glsl")
        {   
            //Default Variables
            this->font = font;
            this->Text = "";
            this->Position = vec2(0);
            this->Scale = vec2(1);
            this->Color = vec3(1);
            this->NewScale = vec2(1);

            this->Name = "";
            this->Tag = "";

            this->Active = true;

            this->texture = new Texture2D("");

            //Buffers + basic Data
            glGenVertexArrays(1, &this->VAO);
            glGenBuffers(1, &this->VBO);
            glBindVertexArray(this->VAO);
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        //Update
        void Update(){
            this->Position *= this->Scale;
        }

        //Update with screen size
        void Update(vec2 Scale){
            this->Scale *= Scale;
            this->NewScale = Scale;
            this->UpdateScale = true;
        }

        //Render Method
        void Render(){	
            Update();
            //If Should Render
            if(this->Active){
                glDisable(GL_DEPTH_TEST);

                //Remove in future
                this->font.UpdateFont();

                //Load texture
                glActiveTexture(this->texture->GetUnit());

                //Shader variables
                //this->shader.set1i(this->texture->GetUnit(), "text");
                this->shader.setMat4fv(UIProjection, "projection");
                this->shader.setVec3f(this->Color, "textColor");
                this->shader.use();

                //Vertex buffer
                glBindVertexArray(this->VAO);

                //Basic positions
                float x = this->Position.x;
                float y = this->Position.y;

                //Iterate over characters
                string::const_iterator c;
                for (c = this->Text.begin(); c != this->Text.end(); c++) 
                {   
                    //Find character
                    Character ch = this->font.GetCharacter(*c);

                    //Calculate positioning
                    float xpos = x + ch.Bearing.x * this->Scale.x;
                    float ypos = y - (ch.Size.y - ch.Bearing.y) * this->Scale.y;

                    //Calculate Sizes
                    float w = ch.Size.x * this->Scale.x;
                    float h = ch.Size.y * this->Scale.y;

                    //Vertex data
                    float vertices[6][4] = {
                        { xpos,     ypos + h,   0.0f, 0.0f },            
                        { xpos,     ypos,       0.0f, 1.0f },
                        { xpos + w, ypos,       1.0f, 1.0f },

                        { xpos,     ypos + h,   0.0f, 0.0f },
                        { xpos + w, ypos,       1.0f, 1.0f },
                        { xpos + w, ypos + h,   1.0f, 0.0f }           
                    };

                    //Textures
                    glBindTexture(GL_TEXTURE_2D, ch.TextureID);

                    //Add to Buffer
                    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
                    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

                    //Draw
                    glBindBuffer(GL_ARRAY_BUFFER, 0);

                    glDrawArrays(GL_TRIANGLES, 0, 6);

                    //Advance X
                    x += (ch.Advance >> 6) * this->Scale.x;
                }

                //Unbinding
                glBindVertexArray(0);
                glBindTexture(GL_TEXTURE_2D, 0);
                shader.unbind();

                glEnable(GL_DEPTH_TEST);
            }
        }
        
        //Render Separate
        void Render(vec2 Pos, string Text, vec3 Color, Font font){	
            //Active
            if(this->Active){
                //glEnable(GL_DEPTH_TEST);

                //Remove Me
                font.UpdateFont();

                //Get Unit
                glActiveTexture(__NextAvailableTextureUnit);

                //Shader
                this->shader.use();
                //this->shader.set1i(__NextAvailableTextureUnit, "text");
                this->shader.setMat4fv(UIProjection, "projection");
                this->shader.setVec3f(Color, "textColor");
                this->shader.use();

                glBindVertexArray(this->VAO);

                float x = Pos.x;
                float y = Pos.y;

                //Iterate over characters
                string::const_iterator c;
                for (c = this->Text.begin(); c != this->Text.end(); c++) 
                {   
                    //Find character
                    Character ch = this->font.GetCharacter(*c);

                    //Calculate positioning
                    float xpos = x + ch.Bearing.x * this->Scale.x;
                    float ypos = y - (ch.Size.y - ch.Bearing.y) * this->Scale.y;

                    //Calculate Sizes
                    float w = ch.Size.x * this->Scale.x;
                    float h = ch.Size.y * this->Scale.y;

                    //Vertex data
                    float vertices[6][4] = {
                        { xpos,     ypos + h,   0.0f, 0.0f },            
                        { xpos,     ypos,       0.0f, 1.0f },
                        { xpos + w, ypos,       1.0f, 1.0f },

                        { xpos,     ypos + h,   0.0f, 0.0f },
                        { xpos + w, ypos,       1.0f, 1.0f },
                        { xpos + w, ypos + h,   1.0f, 0.0f }           
                    };

                    //Textures
                    glBindTexture(GL_TEXTURE_2D, ch.TextureID);

                    //Add to Buffer
                    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
                    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

                    //Draw
                    glBindBuffer(GL_ARRAY_BUFFER, 0);

                    glDrawArrays(GL_TRIANGLES, 0, 6);

                    //Advance X
                    x += (ch.Advance >> 6) * this->Scale.x;
                }
                //Unbind
                glBindVertexArray(0);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }
    };
}