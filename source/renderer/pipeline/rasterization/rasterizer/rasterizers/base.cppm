module;

#include <vector>

export module renderer:pipeline.rasterization.rasterizer.base;

// ============================================================================
// Imports
// ============================================================================

import :drawing_pattern;
import :primitive.topology;
import :structure.prefragment;

// ============================================================================
// Declarations
// ============================================================================

export class Rasterizer
{
public:
    virtual ~Rasterizer() = default;

    virtual std::vector<PreFragment> rasterize(
        const Point &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const = 0;

    virtual std::vector<PreFragment> rasterize(
        const Line &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const = 0;

    virtual std::vector<PreFragment> rasterize(
        const Triangle &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const = 0;
};

// ============================================================================
// EOF
// ============================================================================