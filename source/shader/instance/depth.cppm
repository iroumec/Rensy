module;

#include <cmath>

export module intensifier:instance.depth;

// ============================================================================
// Imports
// ============================================================================

import colour;
import barycentric;
import :instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class DepthColourIntensifier : public ColourIntensifier
{
    const double aZ;
    const double bZ;
    const double cZ;
    const double minZ;
    const double maxZ;

public:
    DepthColourIntensifier(
        double aZ = 0, double bZ = 0, double cZ = 0,
        double minZ = 0, double maxZ = 0)
        : aZ{aZ}, bZ{bZ}, cZ{cZ}, minZ{minZ}, maxZ{maxZ} {}

    constexpr Colour adjustColour(
        const Colour &colour,
        const BarycentricCoordinate &coordinates) const override
    {
        double currentDepth =
            coordinates.alpha * this->aZ +
            coordinates.beta * this->bZ +
            coordinates.gamma * this->cZ;

        double intensity = 1.0;

        if (maxZ != minZ)
            intensity =
                (currentDepth - this->minZ) / (this->maxZ - this->minZ);

        return colour * intensity;
    }
};

// ============================================================================
// EOF
// ============================================================================
