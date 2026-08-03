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
import :pipeline.rasterization.rasterizer.vertex;

// ============================================================================
// Implementations
// ============================================================================

std::vector<Fragment> VertexRasterizer::
    rasterize(
        const Triangle &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const
{

    std::vector<Fragment> fragments;

    Vector2D a = primitive.v0.screenPosition;
    Vector2D b = primitive.v1.screenPosition;
    Vector2D c = primitive.v2.screenPosition;

    Fragment aFragment;
    aFragment.xScreen = a.x();
    aFragment.yScreen = a.y();
    fragments.push_back(aFragment);

    Fragment bFragment;
    bFragment.xScreen = b.x();
    bFragment.yScreen = b.y();
    fragments.push_back(bFragment);

    Fragment cFragment;
    cFragment.xScreen = c.x();
    cFragment.yScreen = c.y();
    fragments.push_back(cFragment);

    return fragments;
}

// ============================================================================
// EOF
// ============================================================================