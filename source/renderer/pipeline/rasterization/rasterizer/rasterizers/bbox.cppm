module;

#include <vector>

export module renderer:pipeline.rasterization.rasterizer.bbox;

// ============================================================================
// Imports
// ============================================================================

import :drawing_pattern;
import :structure.fragment;
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
