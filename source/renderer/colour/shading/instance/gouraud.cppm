module;

#include <cmath>

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
    const double alphaVertexLightIntensity;
    const double betaVertexLightIntensity;
    const double gammaVertexLightIntensity;
    const double ambientLight;

public:
    GouraudShading(
        double alphaVertexLightIntensity, double betaVertexLightIntensity,
        double gammaVertexLightIntensity, double ambientLight = 0.4)
        : alphaVertexLightIntensity(alphaVertexLightIntensity),
          betaVertexLightIntensity(betaVertexLightIntensity),
          gammaVertexLightIntensity(gammaVertexLightIntensity),
          ambientLight{ambientLight}
    {
    }

    constexpr void adjustColour(Fragment &fragment) const override
    {
        BarycentricCoordinate coordinates = fragment.barycentricCoordinates;

        fragment.colour.set(
            fragment.colour.get() *
            (ambientLight +
             coordinates.alpha * alphaVertexLightIntensity +
             coordinates.beta * betaVertexLightIntensity +
             coordinates.gamma * gammaVertexLightIntensity));
    }
};

// ============================================================================
// EOF
// ============================================================================
