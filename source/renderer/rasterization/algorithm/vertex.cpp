module;

#include <cmath>
#include <memory>
#include <vector>
#include <algorithm>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :structure.prefragment;
import :primitive.topology.base;
import :rasterization.algorithm.vertex;

// ============================================================================
// Implementations
// ============================================================================

std::vector<PreFragment>
VertexAlgorithm::
    rasterizePrimitive(
        const Primitive &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const
{
    std::vector<PreFragment> prefragments;

    for (const VertexOut &vertex : primitive.getVertices())
    {
        Vector2D screenPosition = vertex.screenPosition;
        PreFragment prefragment(
            screenPosition.x(),
            screenPosition.y());
        prefragments.push_back(prefragment);
    }

    return prefragments;
}

// ============================================================================
// EOF
// ============================================================================