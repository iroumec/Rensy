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

// The use of std::unique_ptr is required due to the use of a polymorfic
// interface.
void GeometryShader::processPrimitives(
    std::vector<std::unique_ptr<Primitive>> &primitives) const
{
    if (this->primitiveGenerator)
        this->primitiveGenerator->processPrimitives(primitives);

    for (auto &primitive : primitives)
        for (VertexOut &vertex : primitive->getVertices())
        {
            vertex.clipPosition =
                this->projectionTransform.apply(vertex.viewPosition);

            this->logger.traceEvery<1000>(
                "Vertex clip position: {}",
                vertex.clipPosition.toString());
        }

    if (this->lightingModel)
    {
        for (auto &primitive : primitives)
        {
            this->lightingModel->processPrimitive(*primitive);
        }
    }
}

// ============================================================================
// EOF
// ============================================================================
