module;

#include <vector>

export module renderer:pipeline.viewport_transform;

// ============================================================================
// Imports
// ============================================================================

import :transform.viewport;
import :structure.vertex_out;
import :primitive.topology.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export constexpr void applyViewportTransform(
    std::vector<Primitive> &primitives,
    unsigned screenWidth,
    unsigned screenHeight)
{
    ViewportTransform viewportTransform{screenWidth, screenHeight};

    // #pragma omp parallel for
    for (Primitive &primitive : primitives)
        for (VertexOut &vertex : primitive.vertices())
            vertex.screenPosition =
                viewportTransform.apply(vertex.ndcPosition);
}

// ============================================================================
// EOF
// ============================================================================