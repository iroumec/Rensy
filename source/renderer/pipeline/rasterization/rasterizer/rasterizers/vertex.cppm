module;

#include <vector>

export module renderer:pipeline.rasterization.rasterizer.vertex;

// ============================================================================
// Imports
// ============================================================================

import :structure.triangle;
import :structure.fragment;
import :pipeline.rasterization.rasterizer.base;

// ============================================================================
// Declarations
// ============================================================================

export class VertexRasterizer : public Rasterizer
{
public:
    std::vector<Fragment> rasterize(const Triangle &primitive,
                                    unsigned screenWidth,
                                    unsigned screenHeight) const override;
};

// ============================================================================
// EOF
// ============================================================================