module;

#include <memory>

export module renderer:colour.shading.factory.base;

// ============================================================================
// Imports
// ============================================================================

import :structure.triangle;
import :colour.shading.instance.base;

// ============================================================================
// Declarations
// ============================================================================

export class ColourShadingFactory
{

public:
    virtual ~ColourShadingFactory() = default;

    // Sets all the necessary thing needed in common for every point
    // in the triangle.
    virtual std::shared_ptr<ColourShading> instance(
        const Triangle &primitive) const = 0;
};

// ============================================================================
// EOF
// ============================================================================