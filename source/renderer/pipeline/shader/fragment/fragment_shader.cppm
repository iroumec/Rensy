module;

#include <vector>

export module renderer:pipeline.shader.fragment;

// ============================================================================
// Imports
// ============================================================================

import :colour.shading;
import :colour.calculator;
import :structure.fragment;
import :primitive.topology.base;

// ============================================================================
// Declarations
// ============================================================================

export class FragmentShader
{
    const ShadingFactory *shadingFactory = nullptr;

public:
    FragmentShader(const ShadingFactory *shadingFactory = nullptr)
        : shadingFactory(shadingFactory) {}

    void processFragments(std::vector<Fragment> &fragments);
};

// ============================================================================
// EOF
// ============================================================================
