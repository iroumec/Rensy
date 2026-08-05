module;

#include <cmath>

export module renderer:colour.calculator.base;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;
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
        const InterpolationData &interpolationData) const = 0;
};

// ============================================================================
// EOF
// ============================================================================