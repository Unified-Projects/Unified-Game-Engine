#pragma once

//Includes
#include <vector>
#include <map>
#include <string>

#include <GLM/glm.hpp>
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <algorithm>

using namespace std;
using namespace glm;

namespace UnifiedEngine {
    //Pixel
    struct Pixel{
        vec4 Color;
        ivec2 Position;
    };

    class PixelImage{
    private:
        //Image
        vector<vector<Pixel>>Image;
        //Data
        unsigned char* RawData;

        bool First;

        //Delete Old
        void DeleteData(){
            delete this->RawData;
        }

        //Generate From Image
        void GenData(){
            //Sizes
            const int SizeX = this->Size.x;
            const int SizeY = this->Size.y;
            
            //Delete Old
            if(!this->First)
                this->DeleteData();

            //Prealocate
            this->RawData = new unsigned char[SizeX * SizeY *3];

            //Write Color
            for(int y = 0; y < this->Size.y; y++){
                for(int x = 0; x < this->Size.x; x++){
                    //Calc Colors
                    int RI = roundf(this->Image[y][x].Color.x * 255);
                    int GI = roundf(this->Image[y][x].Color.y * 255);
                    int BI = roundf(this->Image[y][x].Color.z * 255);
                    //Write Colors
                    this->RawData[y * SizeX * 3 + x * 3] = RI;
                    this->RawData[y * SizeX * 3 + x * 3 + 1] = GI;
                    this->RawData[y * SizeX * 3 + x * 3 + 2] = BI;
                }
            }
        }
    public:
        //Sizeing
        ivec2 Size;
        
        //Initialise Defualts
        PixelImage(ivec2 Size, vec3 color = vec3(0)){
            this->First = true;
            
            //Size
            this->Size = Size;
            if (this->Size.x < 1){
                this->Size.x = 1;
            }
            if (this->Size.y < 1){
                this->Size.y = 1;
            }  

            //Solid Color
            for(int y = 0; y < this->Size.y; y++){
                this->Image.push_back(vector<Pixel>{});
                for(int x = 0; x < this->Size.x; x++){
                    this->Image[y].push_back(Pixel{vec4(color, 1), ivec2(x, y)});
                    //this->Image[y].push_back(Pixel{vec3(static_cast<float>(x)/this->Size.x, static_cast<float>(y)/this->Size.y, (static_cast<float>(x)+static_cast<float>(y))/(this->Size.x+this->Size.y)),ivec2(x,y)});
                }
            }

            //Generate
            this->GenData();

            this->First = false;
        }

        //Delete Old
        ~PixelImage(){
            this->DeleteData();
        }
        
        //Recolor
        void Configure(ivec2 Size, vec3 color = vec3(0)){

            //Size
            this->Size = Size;
            if (this->Size.x < 1){
                this->Size.x = 1;
            }
            if (this->Size.y < 1){
                this->Size.y = 1;
            }

            //Delete Image
            this->Image.clear();

            //Loop Over Image
            for(int y = 0; y < this->Size.y; y++){
                this->Image.push_back(vector<Pixel>{});
                for(int x = 0; x < this->Size.x; x++){
                    this->Image[y].push_back(Pixel{vec4(color, 1), ivec2(x, y)});
                    //this->Image[y].push_back(Pixel{vec3(static_cast<float>(x)/this->Size.x, static_cast<float>(y)/this->Size.y, (static_cast<float>(x)+static_cast<float>(y))/(this->Size.x+this->Size.y)),ivec2(x,y)});
                }
            }
        }

        //Set Specific Pixel
        void SetPixel(ivec2 Pos, vec3 col){
            if(Pos.y > -1 && Pos.x > -1){
                if(Pos.y < this->Size.y && Pos.x < this->Size.x){
                    this->Image[(this->Size.y - 1) - Pos.y][Pos.x].Color = vec4(col.x/255, col.y/255, col.z/255, 1);
                }
            }
        }

        //Sel Pixel With Alpha
        void SetPixel(ivec2 Pos, vec4 col){
            if(Pos.y > -1 && Pos.x > -1){
                if(Pos.y < this->Size.y && Pos.x < this->Size.x){
                    this->Image[(this->Size.y - 1) - Pos.y][Pos.x].Color = col;
                }
            }
        }

        //Return Generated Data
        unsigned char* ReturnData(){
            this->GenData();
            return this->RawData;
        }
    };
}