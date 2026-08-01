module;

export module renderer:colour.intensifier.instance.base;

// ============================================================================
// Imports
// ============================================================================

import colour;
import barycentric;

// ============================================================================
// Declarations
// ============================================================================

// ----------------------------------------------------------------------------
// Colour Intensifier (Base Class)
// ----------------------------------------------------------------------------

export class ColourIntensifier
{

public:
    virtual ~ColourIntensifier() = default;

    virtual constexpr Colour adjustColour(
        const Colour &colour,
        const BarycentricCoordinate &coordinates) const = 0;
};

// ============================================================================
// EOF
// ============================================================================