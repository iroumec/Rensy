module;

#include <memory>

export module intensifier:factory.base;

// ============================================================================
// Imports
// ============================================================================

import vertex;
import :instance.base;

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
        const Vertex &a, const Vertex &b, const Vertex &c) const = 0;
};

// ============================================================================
// EOF
// ============================================================================