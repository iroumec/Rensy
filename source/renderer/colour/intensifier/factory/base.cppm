module;

#include <memory>

export module renderer:colour.intensifier.factory.base;

// ============================================================================
// Imports
// ============================================================================

import :structure.triangle;
import :colour.intensifier.instance.base;

// ============================================================================
// Declarations
// ============================================================================

// ----------------------------------------------------------------------------
// Colour Itensifier Factory (Base Class)
// ----------------------------------------------------------------------------

export class ColourIntensifierFactory
{

public:
    virtual ~ColourIntensifierFactory() = default;

    // Sets all the necessary thing needed in common for every point
    // in the triangle.
    virtual std::shared_ptr<ColourIntensifier> instance(
        const Triangle &primitive) const = 0;
};

// ============================================================================
// EOF
// ============================================================================