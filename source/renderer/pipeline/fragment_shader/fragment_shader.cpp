module;

#include <vector>
#include <memory>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import colour;
import :colour.calculator;
import :colour.intensifier;
import :structure.fragment;
import :structure.triangle;
import :pipeline.fragment_shader;

// ============================================================================
// Implementations
// ============================================================================

void FragmentShader::processFragments(std::vector<Fragment> &fragments,
                                      const Triangle &primitive)
{
    std::shared_ptr<ColourIntensifier> colourIntensifier = nullptr;

    if (this->colourIntensifierFactory != nullptr)
        colourIntensifier = colourIntensifierFactory->instance(primitive);

    for (Fragment &fragment : fragments)
    {
        Colour colour = colourCalculator.calculateColour(fragment, primitive);

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
