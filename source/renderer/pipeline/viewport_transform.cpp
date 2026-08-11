module;

#include <vector>

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

void ViewportTransformPhase::processPrimitive(
    Primitive &primitive) const
{
    // #pragma omp parallel for
    for (VertexOut &vertex : primitive.getVertices())
    {
        const bool trace = logger.shouldTraceEvery<10000>();

        if (trace)
            this->logger.trace(
                "Before viewport: NDC = {}, clip = {}.",
                vertex.ndcPosition.toString(),
                vertex.clipPosition.toString());

        vertex.screenPosition =
            this->viewportTransform.apply(vertex.ndcPosition);

        if (trace)
            this->logger.trace(
                "After viewport: NDC = {}, clip = {}, screen = {}",
                vertex.ndcPosition.toString(),
                vertex.clipPosition.toString(),
                vertex.screenPosition.toString());
    }
}

// ============================================================================
// EOF
// ============================================================================