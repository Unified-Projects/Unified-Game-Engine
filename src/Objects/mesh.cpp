#include <Unified-Engine/Objects/Mesh/mesh.h>

UnifiedEngine::AABB* UnifiedEngine::computeAABB(const UnifiedEngine::Mesh* mesh)
{
    UnifiedEngine::AABB* box = new UnifiedEngine::AABB{};
    for (const auto& vertex : mesh->vertices)
    {
        box->expand(vertex.position);
    }
    return box;
}