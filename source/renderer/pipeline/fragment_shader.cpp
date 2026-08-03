module;

#include <vector>
#include <memory>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :colour.shading;
import :structure.colour;
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
    std::shared_ptr<Shading> shading = nullptr;

    if (this->shadingFactory != nullptr)
        shading = shadingFactory->instance(primitive);

    for (Fragment &fragment : fragments)
    {
        fragment.colour.set(colourCalculator.calculateColour(fragment, primitive));

        if (shading)
            shading->adjustColour(fragment);
    }
}

// ============================================================================
// EOF
// ============================================================================
