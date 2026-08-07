module;

#include <vector>

export module renderer:pipeline.rasterization.rasterizer.vertex;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology;
import :structure.prefragment;
import :pipeline.rasterization.rasterizer.base;

// ============================================================================
// Declarations
// ============================================================================

export class VertexRasterizer : public Rasterizer
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