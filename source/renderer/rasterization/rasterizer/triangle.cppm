module;

#include <vector>

export module renderer:rasterization.rasterizer.triangle;

// ============================================================================
// Imports
// ============================================================================

import :structure.prefragment; // Because vector needs to know all this things.

// ============================================================================
// Forward Declarations
// ============================================================================

class Triangle;

// ============================================================================
// Declarations
// ============================================================================

export class TriangleRasterizer
{
public:
    virtual ~TriangleRasterizer() = default;

    virtual std::vector<PreFragment> rasterize(
        const Triangle &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const = 0;
};

// ============================================================================
// EOF
// ============================================================================
