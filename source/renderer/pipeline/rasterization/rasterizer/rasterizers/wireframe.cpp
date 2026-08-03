module;

#include <cmath>
#include <memory>
#include <vector>
#include <algorithm>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :math.bresenham;
import :structure.triangle;
import :structure.fragment;
import :pipeline.rasterization.rasterizer.wireframe;

// ============================================================================
// Implementations
// ============================================================================

std::vector<Fragment> WireframeRasterizer::
    rasterize(
        const Triangle &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const
{
    std::vector<Fragment> fragments;

    Vector2D a = primitive.v0.screenPosition;
    Vector2D b = primitive.v1.screenPosition;
    Vector2D c = primitive.v2.screenPosition;

    std::vector<Vector2D> vectors;

    // This order is important for circular colour generators.
    drawLine(a, b, vectors);
    drawLine(c, a, vectors);
    drawLine(b, c, vectors);

    for (Vector2D vector : vectors)
    {
        Fragment fragment;

        fragment.xScreen = vector.x();
        fragment.yScreen = vector.y();

        fragments.push_back(fragment);
    }

    return fragments;
}

// ============================================================================
// EOF
// ============================================================================