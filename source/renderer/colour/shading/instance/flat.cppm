module;

#include <cmath>

export module renderer:colour.shading.instance.flat;

// ============================================================================
// Imports
// ============================================================================

import colour;
import barycentric;
import :colour.shading.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class FlatColourShading : public ColourShading
{
    const double lightIntensity;

public:
    FlatColourShading(double lightIntensity)
        : lightIntensity(lightIntensity) {}

    constexpr Colour adjustColour(
        const Colour &colour,
        const BarycentricCoordinate &coordinates) const override
    {
        return colour + (white * (0.2 + this->lightIntensity));
    }
};

// ============================================================================
// EOF
// ============================================================================
