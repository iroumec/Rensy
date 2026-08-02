module;

#include <cmath>

export module renderer:colour.shading.instance.border;

// ============================================================================
// Imports
// ============================================================================

import :math.barycentric;
import :structure.fragment;
import :colour.shading.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class BorderShading : public Shading
{
public:
    constexpr void adjustColour(Fragment &fragment) const override
    {
        BarycentricCoordinate coordinates = fragment.barycentricCoordinates;

        double intensity =
            std::pow(coordinates.alpha, 2) +
            std::pow(coordinates.beta, 2) +
            std::pow(coordinates.gamma, 2);

        fragment.colour = fragment.colour * intensity;
    }
};

// ============================================================================
// EOF
// ============================================================================