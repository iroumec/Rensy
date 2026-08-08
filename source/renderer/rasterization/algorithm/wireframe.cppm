module;

#include <vector>

export module renderer:rasterization.algorithm.wireframe;

// ============================================================================
// Imports
// ============================================================================

import :structure.prefragment; // Because vector needs to know all this things.
import :rasterization.rasterizer.line;
import :rasterization.rasterizer.triangle;

// ============================================================================
// Forward Declarations
// ============================================================================

class Line;
class Triangle;

// ============================================================================
// Declarations
// ============================================================================

export class WireframeAlgorithm
    : public LineRasterizer,
      public TriangleRasterizer
{
public:
    std::vector<PreFragment> rasterize(
        const Line &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const override;

    std::vector<PreFragment> rasterize(
        const Triangle &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const override;
};

// ============================================================================
// EOF
// ============================================================================