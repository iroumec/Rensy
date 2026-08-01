module;

#include <vector>

export module renderer:pipeline.viewport_transform;

// ============================================================================
// Imports
// ============================================================================

import :structure.triangle;
import :transform.viewport;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export constexpr void applyViewportTransform(
    std::vector<Triangle> &primitives,
    unsigned screenWidth,
    unsigned screenHeight)
{
    ViewportTransform viewportTransform{screenWidth, screenHeight};

    // #pragma omp parallel for
    for (Triangle &primitive : primitives)
    {
        primitive.v0.screenPosition =
            viewportTransform.apply(primitive.v0.ndcPosition);
        primitive.v1.screenPosition =
            viewportTransform.apply(primitive.v1.ndcPosition);
        primitive.v2.screenPosition =
            viewportTransform.apply(primitive.v2.ndcPosition);
    }
}

// ============================================================================
// EOF
// ============================================================================