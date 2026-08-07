module;

#include <vector>

export module renderer:pipeline.interpolator;

// ============================================================================
// Imports
// ============================================================================

import :colour.calculator;
import :structure.fragment;
import :interpolation.data;
import :structure.prefragment;

// ============================================================================
// Declarations
// ============================================================================

export class Interpolator
{
    const ColourCalculator &colourCalculator;

    Fragment interpolate(const PreFragment &prefragment);

public:
    Interpolator(const ColourCalculator &colourCalculator)
        : colourCalculator(colourCalculator) {}

    std::vector<Fragment> interpolate(
        const std::vector<PreFragment> &prefragments);
};

// ============================================================================
// EOF
// ============================================================================