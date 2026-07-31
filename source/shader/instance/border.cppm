module;

#include <cmath>

export module intensifier:instance.border;

// ============================================================================
// Imports
// ============================================================================

import colour;
import barycentric;
import :instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class BorderColourIntensifier : public ColourIntensifier
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