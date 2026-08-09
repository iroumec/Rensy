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
import :interpolation.data;
import :structure.vertex_out;
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
    VertexOut a = primitive.getVertexOne();
    VertexOut b = primitive.getVertexTwo();

    std::vector<Vector2D> vectors;

    drawLine(a.screenPosition, b.screenPosition, vectors);

    std::vector<PreFragment> prefragments;

    for (Vector2D vector : vectors)
    {
        InterpolationData interpolationData{};
        interpolationData.addInfluence(AttributeInfluence(a, 0.5)); // TODO: use t then. Bresenham output.
        interpolationData.addInfluence(AttributeInfluence(b, 0.5));

        PreFragment prefragment(vector.x(), vector.y(), interpolationData);
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