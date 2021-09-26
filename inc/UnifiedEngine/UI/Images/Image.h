#pragma once

//Includes
#include "../../Core/OpenGL/OpenGLInc.h"
#include "../../Maths/Maths.h"
#include "../../Object/Components/Resources.h"
#include "../../Core/Renderer/RenderInfo.h"
#include "../../Core/Renderer/PixelRender.h"

namespace UnifiedEngine {
    class Image{
    private:
        //Buffers
        GLuint id; //Texture
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;
        
        //Vertex
        vector<float> vertices;
        vector<int> indices;

        //Texture Type
        bool RawDataBased = false;
        
        //Comparisons for updating
        ivec2 OldSize;
        vec2 OldScale;
        vec2 OldPos;

        //Renderer
        Shader shader;

        //Scaling
        bool UpdateScale = false;
        vec2 UpdatedScale;

        //Redo Buffers
        void UpdateModel(){
            //Remove old if they exist
            if (this->VAO) {
				glDeleteBuffers(1, &this->VAO);
				glDeleteBuffers(1, &this->VBO);
                glDeleteBuffers(1, &this->EBO);
			}

            //
            //
            //
            // MEMORY LEAK //
            //
            //
            //

            //Redo the Vertex
            this->vertices.erase(this->vertices.begin(), this->vertices.end());
            this->indices.erase(this->indices.begin(), this->indices.end());

            //Vertexes
            this->vertices = { 
                // pos                                                                                                              // tex
                0.0f * (this->Size.x * this->scale.x) + this->Position.x, 1.0f * (this->Size.y * this->scale.y) + this->Position.y, 0.0f, 1.0f,
                1.0f * (this->Size.x * this->scale.x) + this->Position.x, 0.0f * (this->Size.y * this->scale.y) + this->Position.y, 1.0f, 0.0f,
                0.0f * (this->Size.x * this->scale.x) + this->Position.x, 0.0f * (this->Size.y * this->scale.y) + this->Position.y, 0.0f, 0.0f, 

                // pos                                                                                                              // tex
                0.0f * (this->Size.x * this->scale.x) + this->Position.x, 1.0f * (this->Size.y * this->scale.y) + this->Position.y, 0.0f, 1.0f,
                1.0f * (this->Size.x * this->scale.x) + this->Position.x, 1.0f * (this->Size.y * this->scale.y) + this->Position.y, 1.0f, 1.0f,
                1.0f * (this->Size.x * this->scale.x) + this->Position.x, 0.0f * (this->Size.y * this->scale.y) + this->Position.y, 1.0f, 0.0f,
            };

            //Order
            this->indices = {
                2, 1, 0,
                5, 4, 3
            };

            //New Buffers
            glGenVertexArrays(1, &this->VAO);
            glBindVertexArray(this->VAO);

            glGenBuffers(1, &this->VBO);
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

            glGenBuffers(1, &this->EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

            //Join Data
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW); 
            
            //Sort Locations
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

            //Unbind
			glBindVertexArray(0);
        }

        //Redo Texture Data
        /*void UpdateTexture(){
            //Load texture
            glBindTexture(GL_TEXTURE_2D, this->id);

            //
            //
            //
            // MEMORY LEAK //
            //
            //
            //

            //Load New Data
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->Size.x, this->Size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, this->RawImage);
			glGenerateMipmap(GL_TEXTURE_2D);

            //Unbind
			glActiveTexture(0);
			glBindTexture(GL_TEXTURE_2D, 0);
        }*/

    public:
        //Main Organiser
        ivec2 Size;
        vec2 Position;
        vec3 Color;

        //Texturing
        PixelImage* RawImage;
        Texture2D* Texture;

        //Name and Tag for identification
        string name;
        string tag;
        
        //Scale
        vec2 scale;

        //Ensure Scale Every Frame (Can Cause Memory Issues Right Now)
        bool scaleConstant;

        //Init With a Texture2D
        Image(Texture2D* Texture, ivec2 Size, ivec2 Position = ivec2(0))
            : shader("./rsc/DefaultShaders/UI/ImageVertex.glsl", "./rsc/DefaultShaders/UI/ImageFragment.glsl")
        {   
            //Normale Variable Inits
            this->Color = vec3(1);
            this->Size = Size;
            this->OldSize = Size;
            this->Position = Position;
            this->Texture = Texture;
            this->scale = vec2(1);
            this->UpdatedScale = vec2(1);
            this->OldScale = this->scale;
            this->OldPos = this->Position;

            //VAO
            this->UpdateModel();
        }

        //Init with a pixel imgae (Raw Image from Data)
        Image(PixelImage* I, ivec2 Pos = ivec2(0))
            : shader("./rsc/DefaultShaders/UI/ImageVertex.glsl", "./rsc/DefaultShaders/UI/ImageFragment.glsl")
        {
            //Normal Variable Inits
            this->Color = vec3(1);
            this->Position = Pos;
            this->Size = I->Size;
            this->RawDataBased = true;
            this->RawImage = I;
            this->scale = vec2(1);
            this->UpdatedScale = vec2(1);
            this->OldScale = this->scale;
            this->OldPos = this->Position;

            //Texture Init
            this->Texture = new Texture2D(I->ReturnData(), I->Size.x, I->Size.y);

            //VAO
            this->UpdateModel();
        }

        //Updates
        void Update(){
            //Screen Scale Modification
            if(this->UpdateScale || this->scaleConstant){
                this->Position *= this->UpdatedScale;
                this->UpdateModel();
            }
            //Size Modification
            if(this->OldSize != this->Size){
                this->UpdateModel();
                this->OldSize = this->Size;
            }  
            //Self Scale Modification
            if(this->OldScale != this->scale){
                this->UpdateModel();
                this->OldScale = this->scale;
            }
            //Raw Image Update
            if(this->RawDataBased){
                this->Texture->UpdateTexture(this->RawImage->ReturnData(), this->RawImage->Size.x, this->RawImage->Size.y);
            }
            //Position Modification
            if(this->OldPos != this->Position){
                this->OldPos = this->Position;
                UpdateModel();
            }
            this->UpdateScale = false;
        }

        //Screen Scale Update
        void Update(vec2 Scale){
            this->scale *= Scale;
            this->UpdatedScale *= Scale;
            this->UpdateScale = true;
        }

        //Rendering
        void Render(){
            Update();
            if(this->RawDataBased){
                /*this->RawImage->Render(this->id);

                glActiveTexture(__NextAvailableTextureUnit);
                
                this->shader.setMat4fv(UIProjection, "projection");
                this->shader.set1i(__NextAvailableTextureUnit, "text");
                this->shader.setVec3f(this->Color, "textColor");

                this->shader.use();

                glBindTexture(GL_TEXTURE_2D, this->id);
                glBindVertexArray(this->VAO);

                //glDrawArrays(GL_TRIANGLES, 0, 6);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                glBindVertexArray(0);
                glBindTexture(GL_TEXTURE_2D, 0);
                glActiveTexture(0);

                this->shader.unbind();*/

                //Load Image?
                this->Texture->unbind();

                //Load Image
                //glActiveTexture(this->Texture->GetUnit());
                glBindTexture(GL_TEXTURE_2D, this->Texture->GetID());
                
                //Pass other render required variables
                this->shader.setMat4fv(UIProjection, "projection");
                //this->shader.set1i(this->Texture->GetUnit(), "textI");
                this->shader.setVec3f(this->Color, "textColor");

                //Load Shader
                this->shader.use();

                //Binding the Vertexes
                glBindVertexArray(this->VAO);

                //Draw the Shape using Indices
                //glDrawArrays(GL_TRIANGLES, 0, 6);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                //Unbinding
                glBindVertexArray(0);

                this->Texture->unbind();
                this->shader.unbind();
            }
            else{
                //Bind Texture
                this->Texture->bind();
                
                //Load Shader Variables
                this->shader.setMat4fv(UIProjection, "projection");
                this->shader.set1i(this->Texture->GetUnit(), "text");
                this->shader.setVec3f(this->Color, "textColor");

                //Use Shader
                this->shader.use();

                //Bind VAO
                glBindVertexArray(this->VAO);

                //Draw using indices
                //glDrawArrays(GL_TRIANGLES, 0, 6);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                
                //Unbinding
                glBindVertexArray(0);

                this->Texture->unbind();
                this->shader.unbind();
            }
        }
    };
}