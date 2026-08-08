module;

#include <vector>

export module renderer:rasterization.rasterizer.point;

// ============================================================================
// Imports
// ============================================================================

import :structure.prefragment; // Because vector needs to know all this things.

// ============================================================================
// Forward Declarations
// ============================================================================

class Point;

// ============================================================================
// Declarations
// ============================================================================

export class PointRasterizer
{
public:
    virtual ~PointRasterizer() = default;

    virtual std::vector<PreFragment> rasterize(
        const Point &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const = 0;
};

// ============================================================================
// EOF
// ============================================================================
