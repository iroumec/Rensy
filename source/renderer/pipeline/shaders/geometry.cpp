module;

#include <vector>
#include <memory>

module renderer;

// ============================================================================
// Implementations
// ============================================================================

import :primitive.topology.base;
import :pipeline.shader.geometry;

// ============================================================================
// Implementations
// ============================================================================

std::vector<std::unique_ptr<Primitive>> GeometryShader::processPrimitives(
    std::vector<std::unique_ptr<Primitive>> primitives) const
{
    if (this->primitiveGenerator)
        primitives = this->primitiveGenerator->processPrimitives(primitives);

    if (this->lightingModel)
        for (auto &primitive : primitives)
            this->lightingModel->processPrimitive(primitive);

    return primitives;
}

// ============================================================================
// EOF
// ============================================================================
