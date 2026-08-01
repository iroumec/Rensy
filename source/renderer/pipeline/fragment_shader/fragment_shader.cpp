module;

#include <vector>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import colour;
import :colour.intensifier;
import :structure.fragment;
import :structure.triangle;

// ============================================================================
// Implementations
// ============================================================================

void FragmentShader::processFragments(std::vector<Fragment> &fragments,
                                      const Triangle &primitive)
{
    std::shared_ptr<ColourIntensifier> colourIntensifier = nullptr;

    if (colourIntensifierFactory)
        colourIntensifier =
            colourIntensifierFactory->instance(
                primitive.v0,
                primitive.v1,
                primitive.v2);

    for (Fragment &fragment : fragments)
    {
        Colour colour =
            colourCalculator.calculateColour(
                primitive.v0,
                primitive.v1,
                primitive.v2,
                fragment.barycentricCoordinates);

        if (colourIntensifier)
            colour = colourIntensifier->adjustColour(
                colour,
                fragment.barycentricCoordinates);

        fragment.colour = colour;
    }
}

// ============================================================================
// EOF
// ============================================================================
