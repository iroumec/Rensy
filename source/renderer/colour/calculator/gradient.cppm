module;

#include <vector>

export module renderer:colour.calculator.gradient;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;
import :colour.calculator.base;
import :pipeline.interpolation.data;

// ============================================================================
// Declarations
// ============================================================================

/**
 * Returns the colour with the most dominant barycentric coordinate.
 */
export class GradientColourCalculator : public ColourCalculator
{

public:
    constexpr Colour calculateColour(
        const InterpolationData &interpolationData) const override
    {
        Colour result = Colour();

        for (const AttributeInfluence &influence : interpolationData)
            result += influence.vertex.colour.get() * influence.weight;

        return result;
    }
};

// ============================================================================
// EOF
// ============================================================================