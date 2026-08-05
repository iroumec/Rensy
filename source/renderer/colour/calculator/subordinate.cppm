module;

export module renderer:colour.calculator.subordinate;

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
 * Returns the colour with the least dominant barycentric coordinate.
 */
export class SubordinateColourCalculator : public ColourCalculator
{

public:
    constexpr Colour calculateColour(
        const InterpolationData &interpolationData) const override
    {
        const AttributeInfluence *minInfluentialAttribute =
            interpolationData.getMinInfluentialAttribute();

        if (minInfluentialAttribute)
            return minInfluentialAttribute->vertex.colour.get();
        else
            return Colour();
    }
};

// ============================================================================
// EOF
// ============================================================================