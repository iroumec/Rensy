module;

#include <vector>

export module renderer:pipeline.shader.fragment;

// ============================================================================
// Imports
// ============================================================================

import :colour.shading;
import :colour.calculator;
import :structure.fragment;
import :structure.triangle;

// ============================================================================
// Declarations
// ============================================================================

export class FragmentShader
{
    const ColourCalculator &colourCalculator;
    const ShadingFactory *shadingFactory = nullptr;

public:
    FragmentShader(
        const ColourCalculator &colourCalculator,
        const ShadingFactory *shadingFactory = nullptr)
        : colourCalculator(colourCalculator),
          shadingFactory(shadingFactory) {}

    void processFragments(
        std::vector<Fragment> &fragments, const Triangle &primitive);
};

// ============================================================================
// EOF
// ============================================================================
