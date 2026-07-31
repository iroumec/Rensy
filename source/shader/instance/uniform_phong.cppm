module;

#include <cmath>

export module intensifier:instance.uniform_phong;

// ============================================================================
// Imports
// ============================================================================

import colour;
import barycentric;
import :instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class UniformPhongColourIntensifier : public ColourIntensifier
{
    const double lightIntensity;

public:
    UniformPhongColourIntensifier(double lightIntensity)
        : lightIntensity(lightIntensity) {}

    constexpr Colour adjustColour(
        const Colour &colour,
        const BarycentricCoordinate &coordinates) const override
    {
        return colour + white * this->lightIntensity;
    }
};

// ============================================================================
// EOF
// ============================================================================
