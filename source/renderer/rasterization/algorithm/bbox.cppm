module;

#include <vector>

export module renderer:rasterization.algorithm.bbox;

// ============================================================================
// Imports
// ============================================================================

import :structure.prefragment; // Because vector needs to know all this things.
import :rasterization.rasterizer.triangle;

// ============================================================================
// Forward Declarations
// ============================================================================

class Triangle;
class DrawingPattern;

// ============================================================================
// Declarations
// ============================================================================

export class BoundingBoxAlgorithm : public TriangleRasterizer
{
    const DrawingPattern *drawingPattern = nullptr;

public:
    BoundingBoxAlgorithm(
        const DrawingPattern *drawingPattern = nullptr)
        : drawingPattern(drawingPattern) {}

    std::vector<PreFragment> rasterize(
        const Triangle &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const override;
};

// ============================================================================
// EOF
// ============================================================================
