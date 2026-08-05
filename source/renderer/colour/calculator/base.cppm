module;

#include <cmath>

export module renderer:colour.calculator.base;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;
import :structure.fragment;
import :pipeline.interpolation.data;

// ============================================================================
// Declarations
// ============================================================================

/**
 * Given a list of vertex, these classes calculate the final colour.
 *
 */
export class ColourCalculator
{

public:
    virtual ~ColourCalculator() = default;

    virtual constexpr Colour calculateColour(
        const Fragment &fragment,
        const InterpolationData &interpolationData) const = 0;
};

// ============================================================================
// EOF
// ============================================================================