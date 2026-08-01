module;

export module renderer:colour.shading.instance.base;

// ============================================================================
// Imports
// ============================================================================

import colour;
import barycentric;

// ============================================================================
// Declarations
// ============================================================================

export class ColourShading
{

public:
    virtual ~ColourShading() = default;

    virtual constexpr Colour adjustColour(
        const Colour &colour,
        const BarycentricCoordinate &coordinates) const = 0;
};

// ============================================================================
// EOF
// ============================================================================