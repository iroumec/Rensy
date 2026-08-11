module;

#include <cmath>
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

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
    // for (const VertexOut &vertex : primitive.getVertices())
    //     std::cout << vertex.screenPosition << '\n';

    VertexOut a = primitive.getVertexOne();
    VertexOut b = primitive.getVertexTwo();

    std::vector<Vector2D> vectors;

    drawLine(a.screenPosition, b.screenPosition, vectors);

    std::vector<PreFragment> prefragments;

    // std::cout << a.screenPosition << '\n';
    // std::cout << b.screenPosition << '\n';
    // std::cout << vectors.size() << '\n';
    if (
        a.screenPosition.x() > screenWidth ||
        a.screenPosition.y() > screenHeight ||
        b.screenPosition.x() > screenWidth ||
        b.screenPosition.y() > screenHeight)
        throw std::runtime_error(
            "Vertex's screen position out of screen dimensions.");

    for (Vector2D vector : vectors)
    {
        // std::cout << vector << '\n';
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