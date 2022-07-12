#pragma once

#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>
#include <Unified-Engine/debug.h>
#include <list>

namespace UnifiedEngine
{
    struct Color{
        //Components
        float red = 0.0f;
        float green = 0.0f;
        float blue = 0.0f;
        float alpha = 1.0f;
    
    public: //Color Operators
        inline Color operator=(std::initializer_list<int> list){
            if(list.size() > 4){
                return *this;
            }

            float* mem = (float*)(this);
            int x = 0;

            for (auto i = list.begin(); i != list.end(); i++) {
                mem[x] = *i;
                x++;
            }

            return *this;
        }

    public: //Vec3 Operators
        inline Color operator=(glm::vec3 input){
            this->red = input.x;
            this->green = input.y;
            this->blue = input.z;

            return *this;
        }

    public: //Vec 4 Operators
        inline Color operator=(glm::vec4 input){
            this->red = input.x;
            this->green = input.y;
            this->blue = input.z;
            this->alpha = input.w;

            return *this;
        }
    };
} // namespace UnifiedEngine
