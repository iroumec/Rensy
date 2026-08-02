module;

#include <cmath>

export module renderer:colour.shading.instance.depth;

// ============================================================================
// Imports
// ============================================================================

import :math.barycentric;
import :structure.fragment;
import :colour.shading.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class DepthShading : public Shading
{
    const double aZ;
    const double bZ;
    const double cZ;
    const double minZ;
    const double maxZ;

public:
    DepthShading(
        double aZ = 0, double bZ = 0, double cZ = 0,
        double minZ = 0, double maxZ = 0)
        : aZ{aZ}, bZ{bZ}, cZ{cZ}, minZ{minZ}, maxZ{maxZ} {}

    constexpr void adjustColour(Fragment &fragment) const override
    {
        BarycentricCoordinate coordinates = fragment.barycentricCoordinates;

        double currentDepth =
            coordinates.alpha * this->aZ +
            coordinates.beta * this->bZ +
            coordinates.gamma * this->cZ;

        double intensity = 1.0;

        if (maxZ != minZ)
            intensity =
                (currentDepth - this->minZ) / (this->maxZ - this->minZ);

        fragment.colour = fragment.colour * intensity;
    }
};

// ============================================================================
// EOF
// ============================================================================
