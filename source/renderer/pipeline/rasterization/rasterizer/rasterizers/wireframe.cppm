module;

#include <vector>

export module renderer:pipeline.rasterization.rasterizer.wireframe;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;
import :structure.triangle;
import :structure.fragment;
import :math.vector.vector_2d;
import :pipeline.rasterization.rasterizer.base;

// ============================================================================
// Declarations
// ============================================================================

export class WireframeRasterizer : public Rasterizer
{
public:
    std::vector<Fragment> rasterize(
        const Triangle &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const override;
};

Fragment assembleFragment(
    const Colour &aColour, const Colour &bColour,
    unsigned xScreen, unsigned yScrren);

// ============================================================================
// EOF
// ============================================================================