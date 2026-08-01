module;

#include <vector>
#include <memory>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import colour;
import :colour.shading;
import :colour.calculator;
import :structure.fragment;
import :structure.triangle;
import :pipeline.fragment_shader;

// ============================================================================
// Implementations
// ============================================================================

void FragmentShader::processFragments(std::vector<Fragment> &fragments,
                                      const Triangle &primitive)
{
    std::shared_ptr<ColourShading> colourShading = nullptr;

    if (this->colourShadingFactory != nullptr)
        colourShading = colourShadingFactory->instance(primitive);

    for (Fragment &fragment : fragments)
    {
        Colour colour = colourCalculator.calculateColour(fragment, primitive);

        if (colourShading)
            colour = colourShading->adjustColour(
                colour,
                fragment.barycentricCoordinates);

        fragment.colour = colour;
    }
}

// ============================================================================
// EOF
// ============================================================================
