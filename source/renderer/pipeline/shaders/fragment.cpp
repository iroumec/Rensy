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
        this->logger.trace(
            "FRAGMENT SHADER: Light intensity before lighting model: {}",
            fragment.lightIntensity);

        if (this->lightingModel)
            this->lightingModel->processFragment(fragment);

        this->logger.trace(
            "FRAGMENT SHADER: Light intensity after lighting model: {}",
            fragment.lightIntensity);

        // Light intensity should have been previously calculated
        // by a lighting model.
        fragment.colour.set(fragment.colour.get() * fragment.lightIntensity);
    }
}

// ============================================================================
// EOF
// ============================================================================
