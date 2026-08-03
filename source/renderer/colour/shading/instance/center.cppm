module;

#include <cmath>

export module renderer:colour.shading.instance.center;

// ============================================================================
// Imports
// ============================================================================

import :math.barycentric;
import :structure.fragment;
import :colour.shading.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class CenterShading : public Shading
{
public:
    constexpr void adjustColour(Fragment &fragment) const override
    {
        BarycentricCoordinate coordinates = fragment.barycentricCoordinates;

        double intensity = 3 * (std::pow(coordinates.alpha, 2) +
                                std::pow(coordinates.beta, 2) +
                                std::pow(coordinates.gamma, 2));

        fragment.colour.set(fragment.colour.get() * (1 / intensity));
    }
};

// ============================================================================
// EOF
// ============================================================================