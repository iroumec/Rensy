module;

#include <vector>

export module renderer:rasterization.algorithm.vertex;

// ============================================================================
// Imports
// ============================================================================

import :structure.prefragment; // Because vector needs to know all this things.
// Because of the conversion in the private method.
import :primitive.topology.base;
import :primitive.topology.line;
import :primitive.topology.point;
import :primitive.topology.triangle;
import :rasterization.rasterizer.line;
import :rasterization.rasterizer.point;
import :rasterization.rasterizer.triangle;

// ============================================================================
// Declarations
// ============================================================================

export class VertexAlgorithm
    : public PointRasterizer,
      public LineRasterizer,
      public TriangleRasterizer
{
private:
    std::vector<PreFragment> rasterizePrimitive(
        const Primitive &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const;

public:
    std::vector<PreFragment> rasterize(
        const Point &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const override
    {
        return this->rasterizePrimitive(primitive, screenWidth, screenHeight);
    }

    std::vector<PreFragment> rasterize(
        const Line &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const override
    {
        return this->rasterizePrimitive(primitive, screenWidth, screenHeight);
    }

    std::vector<PreFragment> rasterize(
        const Triangle &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const override
    {
        return this->rasterizePrimitive(primitive, screenWidth, screenHeight);
    }
};

// ============================================================================
// EOF
// ============================================================================