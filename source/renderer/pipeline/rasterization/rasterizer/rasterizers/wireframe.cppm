module;

#include <vector>

export module renderer:pipeline.rasterization.rasterizer.wireframe;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology;
import :structure.fragment;
import :pipeline.rasterization.rasterizer.base;

// ============================================================================
// Declarations
// ============================================================================

export class WireframeRasterizer : public Rasterizer
{
public:
    std::vector<Fragment> rasterize(
        const Point &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const override;

    std::vector<Fragment> rasterize(
        const Line &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const override;

    std::vector<Fragment> rasterize(
        const Triangle &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const override;
};

// ============================================================================
// EOF
// ============================================================================