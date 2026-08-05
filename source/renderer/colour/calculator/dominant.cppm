module;

export module renderer:colour.calculator.dominant;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;
import :structure.fragment;
import :colour.calculator.base;
import :pipeline.interpolation.data;

// ============================================================================
// Declarations
// ============================================================================

/**
 * Returns the colour with the most dominant barycentric coordinate.
 */
export class DominantColourCalculator : public ColourCalculator
{

public:
    constexpr Colour calculateColour(
        const Fragment &fragment,
        const InterpolationData &interpolationData) const override
    {
        const AttributeInfluence *maxInfluentialAttribute =
            interpolationData.getMaxInfluentialAttribute();

        if (maxInfluentialAttribute)
            return maxInfluentialAttribute->vertex.colour.get();
        else
            return Colour();
    }
};

// ============================================================================
// EOF
// ============================================================================