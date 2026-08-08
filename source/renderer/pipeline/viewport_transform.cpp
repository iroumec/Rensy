module;

#include <vector>
#include <memory>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :logging.logger;
import :transform.viewport;
import :structure.vertex_out;
import :primitive.topology.base;
import :pipeline.viewport_transform;

// ============================================================================
// Declarations and Implementations
// ============================================================================

void ViewportTransformPhase::processPrimitives(
    std::vector<std::unique_ptr<Primitive>> &primitives) const
{
    // #pragma omp parallel for
    for (auto &primitive : primitives)
        for (VertexOut &vertex : primitive->vertices())
        {
            vertex.screenPosition =
                this->viewportTransform.apply(vertex.ndcPosition);

            this->logger.trace(
                "Vertex's screen position after viewport transform: {}",
                vertex.screenPosition.toString());
        }
}

// ============================================================================
// EOF
// ============================================================================