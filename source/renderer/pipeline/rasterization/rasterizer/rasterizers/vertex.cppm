module;

#include <vector>

export module renderer:pipeline.rasterization.rasterizer.vertex;

// ============================================================================
// Imports
// ============================================================================

import :structure.fragment;
import :primitive.topology;
import :pipeline.rasterization.rasterizer.base;

// ============================================================================
// Declarations
// ============================================================================

export class VertexRasterizer : public Rasterizer
{
private:
    std::vector<Fragment> rasterizePrimitive(
        const Primitive &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const;

public:
    std::vector<Fragment> rasterize(
        const Point &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const override
    {
        return this->rasterizePrimitive(primitive, screenWidth, screenHeight);
    }

    std::vector<Fragment> rasterize(
        const Line &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const override
    {
        return this->rasterizePrimitive(primitive, screenWidth, screenHeight);
    }

    std::vector<Fragment> rasterize(
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