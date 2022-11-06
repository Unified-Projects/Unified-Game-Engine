#pragma once

#include <Unified-Engine/Objects/Mesh/mesh.h>

namespace UnifiedEngine
{
    struct Cube : public Mesh{
        inline Cube(){
            this->vertices = {
            //Position                              //Color                 //Texcoords                   //Normals                 
            //Front
            Vertex{glm::vec3(-.5f, .5f, .5f),       glm::vec3(1.0f),        glm::vec2(0, 1),              glm::vec3(0.f, 0.f, -1.f)},
            Vertex{glm::vec3(-.5f, -.5f, .5f),      glm::vec3(1.0f),        glm::vec2(0, 0),              glm::vec3(0.f, 0.f, -1.f)},
            Vertex{glm::vec3(.5f, -.5f, .5f),       glm::vec3(1.0f),        glm::vec2(1, 0),              glm::vec3(0.f, 0.f, -1.f)},
            Vertex{glm::vec3(.5f, .5f, .5f),        glm::vec3(1.0f),        glm::vec2(1, 1),              glm::vec3(0.f, 0.f, -1.f)},

            //Back
            Vertex{glm::vec3(-.5f, .5f, -.5f),      glm::vec3(1.0f),        glm::vec2(0, 1),              glm::vec3(0.f, 0.f, 1.f)},
            Vertex{glm::vec3(-.5f, -.5f, -.5f),     glm::vec3(1.0f),        glm::vec2(0, 0),              glm::vec3(0.f, 0.f, 1.f)},
            Vertex{glm::vec3(.5f, -.5f, -.5f),      glm::vec3(1.0f),        glm::vec2(1, 0),              glm::vec3(0.f, 0.f, 1.f)},
            Vertex{glm::vec3(.5f, .5f, -.5f),       glm::vec3(1.0f),        glm::vec2(1, 1),              glm::vec3(0.f, 0.f, 1.f)},

            //Left
            Vertex{glm::vec3(-.5f, .5f, -.5f),      glm::vec3(1.0f),        glm::vec2(0, 1),              glm::vec3(1.f, 0.f, 0.f)},
            Vertex{glm::vec3(-.5f, -.5f, -.5f),     glm::vec3(1.0f),        glm::vec2(0, 0),              glm::vec3(1.f, 0.f, 0.f)},
            Vertex{glm::vec3(-.5f, -.5f, .5f),      glm::vec3(1.0f),        glm::vec2(1, 0),              glm::vec3(1.f, 0.f, 0.f)},
            Vertex{glm::vec3(-.5f, .5f, .5f),       glm::vec3(1.0f),        glm::vec2(1, 1),              glm::vec3(1.f, 0.f, 0.f)},

            //Right
            Vertex{glm::vec3(.5f, .5f, -.5f),       glm::vec3(1.0f),        glm::vec2(0, 1),              glm::vec3(-1.f, 0.f, 0.f)},
            Vertex{glm::vec3(.5f, -.5f, -.5f),      glm::vec3(1.0f),        glm::vec2(0, 0),              glm::vec3(-1.f, 0.f, 0.f)},
            Vertex{glm::vec3(.5f, -.5f, .5f),       glm::vec3(1.0f),        glm::vec2(1, 0),              glm::vec3(-1.f, 0.f, 0.f)},
            Vertex{glm::vec3(.5f, .5f, .5f),        glm::vec3(1.0f),        glm::vec2(1, 1),              glm::vec3(-1.f, 0.f, 0.f)},

            //Top
            Vertex{glm::vec3(-.5f, .5f, -.5f),      glm::vec3(1.0f),        glm::vec2(0, 1),              glm::vec3(0.f, -1.f, 0.f)},
            Vertex{glm::vec3(-.5f, .5f, .5f),       glm::vec3(1.0f),        glm::vec2(0, 0),              glm::vec3(0.f, -1.f, 0.f)},
            Vertex{glm::vec3(.5f, .5f, .5f),        glm::vec3(1.0f),        glm::vec2(1, 0),              glm::vec3(0.f, -1.f, 0.f)},
            Vertex{glm::vec3(.5f, .5f, -.5f),       glm::vec3(1.0f),        glm::vec2(1, 1),              glm::vec3(0.f, -1.f, 0.f)},

            //bottom
            Vertex{glm::vec3(-.5f, -.5f, -.5f),     glm::vec3(1.0f),        glm::vec2(0, 1),              glm::vec3(0.f, 1.f, 0.f)},
            Vertex{glm::vec3(-.5f, -.5f, .5f),      glm::vec3(1.0f),        glm::vec2(0, 0),              glm::vec3(0.f, 1.f, 0.f)},
            Vertex{glm::vec3(.5f, -.5f, .5f),       glm::vec3(1.0f),        glm::vec2(1, 0),              glm::vec3(0.f, 1.f, 0.f)},
            Vertex{glm::vec3(.5f, -.5f, -.5f),      glm::vec3(1.0f),        glm::vec2(1, 1),              glm::vec3(0.f, 1.f, 0.f)}
        };

        //Indices
        this->indices = {
            0, 1, 2,
            0, 2, 3,

            6, 5, 4,
            7, 6, 4,

            8, 9, 10,
            8, 10, 11,

            14, 13, 12,
            15, 14, 12,

            16, 17, 18,
            16, 18, 19,

            22, 21, 20,
            23, 22, 20
        };
        }
    };
} // namespace UnifiedEngine
