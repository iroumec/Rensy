module;

#include <cmath>
#include <vector>

export module renderer:colour.shading.instance.gouraud;

// ============================================================================
// Imports
// ============================================================================

import :math.barycentric;
import :structure.fragment;
import :colour.shading.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class GouraudShading : public Shading
{
    const std::vector<double> lightIntensities;
    const double ambientLight;

public:
    GouraudShading(
        const std::vector<double> lightIntensities,
        double ambientLight = 0.4)
        : lightIntensities{lightIntensities}, ambientLight{ambientLight} {}

    constexpr void adjustColour(Fragment &fragment) const override
    {
        BarycentricCoordinate coordinates = fragment.barycentricCoordinates;

        fragment.colour.set(
            fragment.colour.get() *
            (ambientLight +
             coordinates.alpha * lightIntensities[0] +
             coordinates.beta * lightIntensities[1] +
             coordinates.gamma * lightIntensities[2]));
    }
};

// ============================================================================
// EOF
// ============================================================================
