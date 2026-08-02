module;

#include <cmath>

export module renderer:colour.shading.instance.gouraud;

// ============================================================================
// Imports
// ============================================================================

import colour;
import barycentric;
import :colour.shading.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class GouraudColourShading : public ColourShading
{
    const double alphaVertexLightIntensity;
    const double betaVertexLightIntensity;
    const double gammaVertexLightIntensity;
    const double ambientLight;

public:
    GouraudColourShading(
        double alphaVertexLightIntensity, double betaVertexLightIntensity,
        double gammaVertexLightIntensity, double ambientLight = 0.4)
        : alphaVertexLightIntensity(alphaVertexLightIntensity),
          betaVertexLightIntensity(betaVertexLightIntensity),
          gammaVertexLightIntensity(gammaVertexLightIntensity),
          ambientLight{ambientLight}
    {
    }

    constexpr Colour adjustColour(
        const Colour &colour,
        const BarycentricCoordinate &coordinates) const override
    {
        return colour * (ambientLight +
                         coordinates.alpha * alphaVertexLightIntensity +
                         coordinates.beta * betaVertexLightIntensity +
                         coordinates.gamma * gammaVertexLightIntensity);
    }
};

// ============================================================================
// EOF
// ============================================================================
