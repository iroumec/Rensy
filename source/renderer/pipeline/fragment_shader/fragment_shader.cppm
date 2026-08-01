module;

#include <vector>

export module renderer:pipeline.fragment_shader;

// ============================================================================
// Imports
// ============================================================================

import :colour.calculator;
import :colour.intensifier;
import :structure.fragment;
import :structure.triangle;

// ============================================================================
// Declarations
// ============================================================================

export class FragmentShader
{
    const ColourCalculator &colourCalculator;
    const ColourIntensifierFactory *colourIntensifierFactory = nullptr;

public:
    FragmentShader(
        const ColourCalculator &colourCalculator,
        const ColourIntensifierFactory *colourIntensifierFactory = nullptr)
        : colourCalculator(colourCalculator),
          colourIntensifierFactory(colourIntensifierFactory) {}

    void processFragments(
        std::vector<Fragment> &fragments, const Triangle &primitive);
};

// ============================================================================
// EOF
// ============================================================================
