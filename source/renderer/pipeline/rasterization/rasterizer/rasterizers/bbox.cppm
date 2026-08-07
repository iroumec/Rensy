module;

#include <vector>

export module renderer:pipeline.rasterization.rasterizer.bbox;

// ============================================================================
// Imports
// ============================================================================

import :drawing_pattern;
import :structure.prefragment;
import :primitive.topology.base;
import :pipeline.rasterization.rasterizer.base;

// ============================================================================
// Declarations
// ============================================================================

export class BoundingBoxRasterizer : public Rasterizer
{
    const DrawingPattern *drawingPattern = nullptr;

public:
    BoundingBoxRasterizer(
        const DrawingPattern *drawingPattern = nullptr)
        : drawingPattern(drawingPattern) {}

    std::vector<PreFragment> rasterize(
        const Point &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const override;

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
