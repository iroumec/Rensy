module;

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

public:
    Interpolator(const ColourCalculator &colourCalculator)
        : colourCalculator(colourCalculator) {}

    Fragment interpolate(const PreFragment &prefragments);
};

// ============================================================================
// EOF
// ============================================================================