module;

#include <vector>

export module renderer:pipeline.rasterization.rasterizer.bbox;

// ============================================================================
// Imports
// ============================================================================

import :drawing_pattern;
import :structure.triangle;
import :structure.fragment;
import :normal.rasterizer.base;
import :pipeline.rasterization.rasterizer.base;

// ============================================================================
// Declarations
// ============================================================================

export class BoundingBoxRasterizer : public Rasterizer
{
    const DrawingPattern *drawingPattern = nullptr;
    const NormalRasterizer *normalRasterizer = nullptr;

public:
    BoundingBoxRasterizer(
        const DrawingPattern *drawingPattern = nullptr,
        const NormalRasterizer *normalRasterizer = nullptr)
        : drawingPattern(drawingPattern), normalRasterizer(normalRasterizer) {}

    std::vector<Fragment> rasterize(const Triangle &primitive,
                                    unsigned screenWidth,
                                    unsigned screenHeight) const override;
};

// ============================================================================
// EOF
// ============================================================================
