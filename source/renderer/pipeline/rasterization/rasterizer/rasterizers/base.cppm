module;

#include <vector>
#include <memory>
#include <utility>

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

    std::vector<PreFragment> rasterize(
        std::vector<std::unique_ptr<Primitive>> &primitives,
        unsigned screenWidth,
        unsigned screenHeight) const = 0;

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