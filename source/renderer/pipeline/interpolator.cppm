module;

export module renderer:pipeline.interpolator;

// ============================================================================
// Imports
// ============================================================================

import :logging.logger;
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
    const Logger &logger;

public:
    Interpolator(
        const ColourCalculator &colourCalculator, const Logger &logger)
        : colourCalculator{colourCalculator}, logger{logger} {}

    Fragment interpolate(const PreFragment &prefragments);
};

// ============================================================================
// EOF
// ============================================================================