module;

#include <vector>
#include <memory>

module renderer;

// ============================================================================
// Implementations
// ============================================================================

std::vector<std::unique_ptr<Primitive>> GeometryShader::processPrimitives(
    std::vector<std::unique_ptr<Primitive>> primitives) const
{
    if (this->primitiveGenerator)
        this->primitiveGenerator->processPrimitives(primitives);

    if (this->lightingModel)
        for (Primitive &primitive : primitives)
            this->lightingModel->processPrimitive(primitives);

    return primitives;
}

// ============================================================================
// EOF
// ============================================================================
