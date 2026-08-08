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
import :structure.prefragment;
import :rasterization.algorithm.wireframe;

// ============================================================================
// Implementations
// ============================================================================

std::vector<PreFragment> WireframeAlgorithm::rasterize(
    const Line &primitive,
    unsigned screenWidth,
    unsigned screenHeight) const
{
    Vector2D a = primitive.getVertexOne().screenPosition;
    Vector2D b = primitive.getVertexTwo().screenPosition;

    std::vector<Vector2D> vectors;

    drawLine(a, b, vectors);

    std::vector<PreFragment> prefragments;

    for (Vector2D vector : vectors)
    {
        PreFragment prefragment(vector.x(), vector.y());
        prefragments.push_back(prefragment);
    }

    return prefragments;
}

std::vector<PreFragment> WireframeAlgorithm::
    rasterize(
        const Triangle &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const
{
    std::vector<PreFragment> prefragments;

    Vector2D a = primitive.getVertexOne().screenPosition;
    Vector2D b = primitive.getVertexTwo().screenPosition;
    Vector2D c = primitive.getVertexThree().screenPosition;

    std::vector<Vector2D> vectors;

    // This order is important for circular colour generators.
    drawLine(a, b, vectors);
    drawLine(c, a, vectors);
    drawLine(b, c, vectors);

    for (Vector2D vector : vectors)
    {
        // PreFragment prefragment(vector.x(), vector.y());
        prefragments.push_back(PreFragment(vector.x(), vector.y()));
    }

    return prefragments;
}

// ============================================================================
// EOF
// ============================================================================