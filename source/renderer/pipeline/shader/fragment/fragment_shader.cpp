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
import :primitive.topology.base;
import :pipeline.shader.fragment;

// ============================================================================
// Implementations
// ============================================================================

void FragmentShader::processFragments(std::vector<Fragment> &fragments)
{
    std::shared_ptr<Shading> shading = nullptr;

    if (this->shadingFactory)
    {
        shading = shadingFactory->instance(primitive);

        for (Fragment &fragment : fragments)
            shading->adjustColour(fragment);
    }
}

// ============================================================================
// EOF
// ============================================================================
