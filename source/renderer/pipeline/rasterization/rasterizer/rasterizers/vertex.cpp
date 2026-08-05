module;

#include <cmath>
#include <memory>
#include <vector>
#include <algorithm>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :structure.fragment;
import :structure.vertex_out;
import :primitive.topology.base;
import :pipeline.rasterization.rasterizer.vertex;

// ============================================================================
// Implementations
// ============================================================================

std::vector<Fragment>
VertexRasterizer::
    rasterizePrimitive(
        const Primitive &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const
{
    std::vector<Fragment> fragments;

    for (const VertexOut &vertex : primitive.vertices())
    {
        Vector2D screenPosition = vertex.screenPosition;
        Fragment fragment;
        fragment.xScreen = screenPosition.x();
        fragment.yScreen = screenPosition.y();
        fragments.push_back(fragment);
    }

    return fragments;
}

// ============================================================================
// EOF
// ============================================================================