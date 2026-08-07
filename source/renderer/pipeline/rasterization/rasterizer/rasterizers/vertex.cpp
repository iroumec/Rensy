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
import :pipeline.rasterization.rasterizer.vertex;

// ============================================================================
// Implementations
// ============================================================================

std::vector<PreFragment>
VertexRasterizer::
    rasterizePrimitive(
        const Primitive &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const
{
    std::vector<PreFragment> prefragments;

    for (const VertexOut &vertex : primitive.vertices())
    {
        Vector2D screenPosition = vertex.screenPosition;
        PreFragment prefragment;
        prefragment.xScreen = screenPosition.x();
        prefragment.yScreen = screenPosition.y();
        prefragments.push_back(prefragment);
    }

    return prefragments;
}

// ============================================================================
// EOF
// ============================================================================