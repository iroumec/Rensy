module;

export module viewport_transform;

// ============================================================================
// Imports
// ============================================================================

import triangle;
import transform;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export constexpr void applyViewportTransform(
    std::vector<Triangles> &primitives,
    unsigned screenWidth,
    unsigned screenHeight)
{
    ViewportTransform viewportTransform{screenWidth, screenHeight};

    // #pragma omp parallel for
    for (primitive : primitives)
    {
        primitive.v0.screenPositionn = viewportTransform.apply(primitive.v0);
        primitive.v1.screenPositionn = viewportTransform.apply(primitive.v1);
        primitive.v2.screenPositionn = viewportTransform.apply(primitive.v2);
    }
}

// ============================================================================
// EOF
// ============================================================================