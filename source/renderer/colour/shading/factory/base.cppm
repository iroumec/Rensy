module;

#include <memory>

export module renderer:colour.shading.factory.base;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology;
import :colour.shading.instance.base;

// ============================================================================
// Declarations
// ============================================================================

export class ShadingFactory
{

public:
    virtual ~ShadingFactory() = default;

    std::shared_ptr<Shading> instance(
        const Point &primitive) const
    {
        return nullptr;
    }

    std::shared_ptr<Shading> instance(
        const Line &primitive) const
    {
        return nullptr;
    }

    // Sets all the necessary thing needed in common for every point
    // in the triangle.
    virtual std::shared_ptr<Shading> instance(
        const Triangle &primitive) const = 0;
};

// ============================================================================
// EOF
// ============================================================================