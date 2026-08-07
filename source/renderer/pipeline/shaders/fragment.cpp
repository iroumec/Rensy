module;

#include <vector>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;
import :structure.fragment;
import :lighting.model.base;
import :primitive.topology.base;
import :pipeline.shader.fragment;

// ============================================================================
// Implementations
// ============================================================================

void FragmentShader::processFragments(std::vector<Fragment> &fragments)
{
    for (Fragment &fragment : fragments)
    {
        if (this->lightingModel)
            this->lightingModel->processFragment(fragment);

        // Light intensity should have been previously calculated
        // by a lighting model.
        fragment.colour *= fragment.lightIntensity;
    }
}

// ============================================================================
// EOF
// ============================================================================
