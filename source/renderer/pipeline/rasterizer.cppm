module;

#include <vector>

export module renderer:pipeline.rasterizer;

// ============================================================================
// Imports
// ============================================================================

import :rasterization.context;

// ============================================================================
// Forward Declarations
// ============================================================================

class Primitive;
class PreFragment;
class LineRasterizer;
class PointRasterizer;
class TriangleRasterizer;

// ============================================================================
// Declarations
// ============================================================================

export class Rasterizer
{
    const RasterizationContext context;

public:
    Rasterizer(
        const PointRasterizer &pointRasterizer,
        const LineRasterizer &lineRasterizer,
        const TriangleRasterizer &triangleRasterizer,
        unsigned screenWidth, unsigned screenHeight)
        : context(
              pointRasterizer,
              lineRasterizer,
              triangleRasterizer,
              screenWidth,
              screenHeight) {}

    std::vector<PreFragment> rasterize(const Primitive &primitive);
};

// ============================================================================
// EOF
// ============================================================================
