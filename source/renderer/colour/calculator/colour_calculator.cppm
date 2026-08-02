module;

#include <cmath>

export module renderer:colour.calculator;

import :structure.colour;
import :math.barycentric;
import :structure.fragment;
import :structure.triangle;

/**
 * Given a list of vertex, these classes calculate the final colour.
 *
 */
export class ColourCalculator
{

public:
    virtual ~ColourCalculator() = default;

    virtual constexpr Colour calculateColour(
        const Fragment &fragment, const Triangle &primitive) const = 0;
};

/**
 * Returns the colour with the most dominant barycentric coordinate.
 */
export class DominantColourCalculator : public ColourCalculator
{

public:
    constexpr Colour calculateColour(
        const Fragment &fragment, const Triangle &primitive) const override
    {
        BarycentricCoordinate coordinates = fragment.barycentricCoordinates;

        if (coordinates.alpha >= coordinates.beta && coordinates.alpha >= coordinates.gamma)
            return primitive.v0.colour;
        else if (coordinates.beta >= coordinates.alpha && coordinates.beta >= coordinates.gamma)
            return primitive.v1.colour;
        else
            return primitive.v2.colour;
    }
};

export class SubordinateColourCalculator : public ColourCalculator
{

public:
    constexpr Colour calculateColour(
        const Fragment &fragment, const Triangle &primitive) const override
    {
        BarycentricCoordinate coordinates = fragment.barycentricCoordinates;

        if (coordinates.alpha <= coordinates.beta && coordinates.alpha <= coordinates.gamma)
            return primitive.v0.colour;
        else if (coordinates.beta <= coordinates.alpha && coordinates.beta <= coordinates.gamma)
            return primitive.v1.colour;
        else
            return primitive.v2.colour;
    }
};

export class GradientColourCalculator : public ColourCalculator
{

public:
    constexpr Colour calculateColour(
        const Fragment &fragment, const Triangle &primitive) const override
    {
        BarycentricCoordinate coordinates = fragment.barycentricCoordinates;

        return coordinates.alpha * primitive.v0.colour +
               coordinates.beta * primitive.v1.colour +
               coordinates.gamma * primitive.v2.colour;
    }
};