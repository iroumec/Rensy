module;

#include <cmath>
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :math.bresenham;
import :primitive.topology;
import :structure.fragment;
import :pipeline.rasterization.rasterizer.wireframe;

// ============================================================================
// Implementations
// ============================================================================

std::vector<Fragment> WireframeRasterizer::rasterize(
    const Point &primitive,
    unsigned screenWidth,
    unsigned screenHeight) const
{
    throw std::invalid_argument("Wireframe rasterizer doesn't support points.");
}

std::vector<Fragment> WireframeRasterizer::rasterize(
    const Line &primitive,
    unsigned screenWidth,
    unsigned screenHeight) const
{
    Vector2D a = primitive.vertexOne().screenPosition;
    Vector2D b = primitive.vertexTwo().screenPosition;

    std::vector<Vector2D> vectors;

    drawLine(a, b, vectors);

    for (Vector2D vector : vectors)
    {
        Fragment fragment;

        fragment.xScreen = vector.x();
        fragment.yScreen = vector.y();

        fragments.push_back(fragment);
    }
}

std::vector<Fragment> WireframeRasterizer::
    rasterize(
        const Triangle &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const
{
    std::vector<Fragment> fragments;

    Vector2D a = primitive.vertexOne().screenPosition;
    Vector2D b = primitive.vertexTwo().screenPosition;
    Vector2D c = primitive.vertexThree().screenPosition;

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