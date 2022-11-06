#pragma once

#include <Unified-Engine/Objects/objectComponent.h>
#include <GLM/vec3.hpp>
#include <Unified-Engine/Objects/Mesh/mesh.h>

namespace UnifiedEngine
{
    enum ColliderType{
        COLLIDER_BOX = 1,
        COLLIDER_SPHERE,
        COLLIDER_MESH
    };

    class BoxCollider;
    class SphericalCollider;

    class Collider : public ObjectComponent{
    public: //CollisionChecks

    public:
        glm::vec3 Offset = glm::vec3(0.0f);
    };

    class BoxCollider : public Collider{
    public:
        glm::vec3 Size = glm::vec3(0.0f);
    };

    class SphericalCollider : public Collider{
    public:
        float Radius = 0.0f;
    };

    class MeshCollider : public Collider{
    public:
        Mesh mesh = {};
    };
} // namespace UnifiedEngine
