module;

export module renderer:colour.calculator.dominant;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;
import :math.barycentric;
import :structure.fragment;
import :primitive.topology;
import :colour.calculator.base;

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
        const Fragment &fragment, const Point &primitive) const override
    {
        return fragment.colour; // TODO
    }

    constexpr Colour calculateColour(
        const Fragment &fragment, const Line &primitive) const override
    {
        return fragment.colour; // TODO
    }

    constexpr Colour calculateColour(
        const Fragment &fragment, const Triangle &primitive) const override
    {
        BarycentricCoordinate coordinates = fragment.barycentricCoordinates;

        if (coordinates.alpha >= coordinates.beta && coordinates.alpha >= coordinates.gamma)
            return primitive.vertexOne().colour.get();
        else if (coordinates.beta >= coordinates.alpha && coordinates.beta >= coordinates.gamma)
            return primitive.vertexTwo().colour.get();
        else
            return primitive.vertexThree().colour.get();
    }
};

// ============================================================================
// EOF
// ============================================================================