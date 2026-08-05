module;

export module renderer:colour.calculator.gradient;

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
export class GradientColourCalculator : public ColourCalculator
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

        return coordinates.alpha * primitive.vertexOne().colour.get() +
               coordinates.beta * primitive.vertexTwo().colour.get() +
               coordinates.gamma * primitive.vertexThree().colour.get();
    }
};

// ============================================================================
// EOF
// ============================================================================