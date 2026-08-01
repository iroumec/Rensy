module;

#include <cmath>

export module renderer:colour.intensifier.instance.center;

// ============================================================================
// Imports
// ============================================================================

import colour;
import barycentric;
import :colour.intensifier.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class CenterColourIntensifier : public ColourIntensifier
{
public:
    constexpr Colour adjustColour(
        const Colour &colour,
        const BarycentricCoordinate &coordinates) const override
    {
        double intensity = 3 * (std::pow(coordinates.alpha, 2) +
                                std::pow(coordinates.beta, 2) +
                                std::pow(coordinates.gamma, 2));

        return colour * (1 / intensity);
    }
};

// ============================================================================
// EOF
// ============================================================================