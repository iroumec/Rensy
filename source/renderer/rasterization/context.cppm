module;

#include <vector>

export module renderer:rasterization.context;

// ============================================================================
// Imports
// ============================================================================

import :structure.prefragment; // Because vector needs to know all this things.
import :rasterization.rasterizer.line;
import :rasterization.rasterizer.point;
import :rasterization.rasterizer.triangle;

// ============================================================================
// Forward Declarations
// ============================================================================

class Line;
class Point;
class Triangle;

// ============================================================================
// Declarations
// ============================================================================

// See resources/documentation/diagrams/rasterization.mmd.
export class RasterizationContext
{
    const PointRasterizer &pointRasterizer;
    const LineRasterizer &lineRasterizer;
    const TriangleRasterizer &triangleRasterizer;
    unsigned screenWidth;
    unsigned screenHeight;

public:
    RasterizationContext(
        const PointRasterizer &pointRasterizer,
        const LineRasterizer &lineRasterizer,
        const TriangleRasterizer &triangleRasterizer,
        unsigned screenWidth, unsigned screenHeight)
        : pointRasterizer{pointRasterizer}, lineRasterizer{lineRasterizer},
          triangleRasterizer{triangleRasterizer}, screenWidth{screenWidth},
          screenHeight{screenHeight} {}

    std::vector<PreFragment> rasterizePoint(const Point &point)
    {
        this->pointRasterizer.rasterize(
            point, this->screenWidth, this->screenHeight);
    }

    std::vector<PreFragment> rasterizeLine(const Line &line)
    {
        this->lineRasterizer.rasterize(
            line, this->screenWidth, this->screenHeight);
    }

    std::vector<PreFragment> rasterizeTriangle(const Triangle &triangle)
    {
        this->triangleRasterizer.rasterize(
            triangle, this->screenWidth, this->screenHeight);
    }
};

// ============================================================================
// Imports
// ============================================================================