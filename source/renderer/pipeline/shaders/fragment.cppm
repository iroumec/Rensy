module;

#include <vector>

export module renderer:pipeline.shader.fragment;

// ============================================================================
// Imports
// ============================================================================

import :colour.calculator;
import :structure.fragment;
import :lighting.model.base;

// ============================================================================
// Declarations
// ============================================================================

export class FragmentShader
{
    const LightingModel *lightingModel;

public:
    FragmentShader(const LightingModel *lightingModel = nullptr)
        : lightingModel(lightingModel) {}

    void processFragments(std::vector<Fragment> &fragments);
};

// ============================================================================
// EOF
// ============================================================================
