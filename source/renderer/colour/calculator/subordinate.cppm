module;

export module renderer:colour.calculator.subordinate;

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
 * Returns the colour with the least dominant barycentric coordinate.
 */
export class SubordinateColourCalculator : public ColourCalculator
{

public:
    constexpr Colour calculateColour(
        const Fragment &fragment,
        const InterpolationData &interpolationData) const override
    {
        AttributeInfluence *minInfluentialAttribute =
            interpolationData.getMinInfluentialAttribute();

        if (minInfluentialAttribute != nullptr)
            return minInfluentialAttribute.vertex.colour.get();
        else
            return Colour();

        Colour result = Colour();
    }
};

// ============================================================================
// EOF
// ============================================================================