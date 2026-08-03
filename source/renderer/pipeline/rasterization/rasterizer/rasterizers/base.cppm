module;

#include <vector>

export module renderer:pipeline.rasterization.rasterizer.base;

// ============================================================================
// Imports
// ============================================================================

import :drawing_pattern;
import :structure.triangle;
import :structure.fragment;

// ============================================================================
// Declarations
// ============================================================================

export class Rasterizer
{
public:
    virtual ~Rasterizer() = default;

    virtual std::vector<Fragment> rasterize(
        const Triangle &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const = 0;
};

// ============================================================================
// EOF
// ============================================================================