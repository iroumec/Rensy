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

    VertexOut a = primitive.getVertexOne();
    VertexOut b = primitive.getVertexTwo();
    VertexOut c = primitive.getVertexThree();

    std::vector<Vector2D> vectors;

    // This order is important for circular colour generators.
    drawLine(a.screenPosition, b.screenPosition, vectors);
    drawLine(c.screenPosition, a.screenPosition, vectors);
    drawLine(b.screenPosition, c.screenPosition, vectors);

    for (Vector2D vector : vectors)
    {
        InterpolationData interpolationData{};
        interpolationData.addInfluence(AttributeInfluence(a, 0.3));
        interpolationData.addInfluence(AttributeInfluence(b, 0.3));
        interpolationData.addInfluence(AttributeInfluence(c, 0.3));

        PreFragment prefragment(vector.x(), vector.y(), interpolationData);
        prefragments.push_back(prefragment);
    }

    return prefragments;
}

// ============================================================================
// EOF
// ============================================================================