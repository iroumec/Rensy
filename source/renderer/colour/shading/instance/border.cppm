module;

#include <cmath>

export module renderer:colour.shading.instance.border;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;
import :math.barycentric;
import :colour.shading.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class BorderColourShading : public ColourShading
{
public:
    constexpr Colour adjustColour(
        const Colour &colour,
        const BarycentricCoordinate &coordinates) const override
    {
        double intensity =
            std::pow(coordinates.alpha, 2) +
            std::pow(coordinates.beta, 2) +
            std::pow(coordinates.gamma, 2);

        return colour * intensity;
    }
};

// ============================================================================
// EOF
// ============================================================================