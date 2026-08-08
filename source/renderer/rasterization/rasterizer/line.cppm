

module;

#include <vector>

export module renderer:rasterization.rasterizer.line;

// ============================================================================
// Imports
// ============================================================================

import :structure.prefragment; // Because vector needs to know all this things.

// ============================================================================
// Forward Declarations
// ============================================================================

class Line;

// ============================================================================
// Declarations
// ============================================================================

export class LineRasterizer
{
public:
    virtual ~LineRasterizer() = default;

    virtual std::vector<PreFragment> rasterize(
        const Line &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const = 0;
};

// ============================================================================
// EOF
// ============================================================================
