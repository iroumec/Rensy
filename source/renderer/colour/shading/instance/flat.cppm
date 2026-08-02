module;

#include <cmath>

export module renderer:colour.shading.instance.flat;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;
import :math.barycentric;
import :colour.shading.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class FlatColourShading : public ColourShading
{
    const double lightIntensity;
    const double ambientLight;

public:
    FlatColourShading(double lightIntensity, double ambientLight = 0.0)
        : lightIntensity(lightIntensity), ambientLight{ambientLight} {}

    constexpr Colour adjustColour(
        const Colour &colour,
        const BarycentricCoordinate &coordinates) const override
    {
        return colour + (white * (ambientLight + this->lightIntensity));
    }
};

// ============================================================================
// EOF
// ============================================================================
