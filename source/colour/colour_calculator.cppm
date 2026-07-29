module;

#include <cmath>

export module colour_calculator;

import vertex;
import colour;
import barycentric;

/**
 * Given a list of vertex, these classes calculate the final colour.
 *
 */
export class ColourCalculator
{

public:
    virtual ~ColourCalculator() = default;

    virtual constexpr Colour calculateColour(const Vertex &a, const Vertex &b, const Vertex &c, const BarycentricCoordinate &coordinates) const = 0;
};

/**
 * Returns the colour with the most dominant barycentric coordinate.
 */
export class DominantColourCalculator : public ColourCalculator
{

public:
    constexpr Colour calculateColour(const Vertex &a, const Vertex &b, const Vertex &c, const BarycentricCoordinate &coordinates) const override
    {
        if (coordinates.alpha >= coordinates.beta && coordinates.alpha >= coordinates.gamma)
            return a.getColour();
        else if (coordinates.beta >= coordinates.alpha && coordinates.beta >= coordinates.gamma)
            return b.getColour();
        else
            return c.getColour();
    }
};

export class SubordinateColourCalculator : public ColourCalculator
{

public:
    constexpr Colour calculateColour(const Vertex &a, const Vertex &b, const Vertex &c, const BarycentricCoordinate &coordinates) const override
    {
        if (coordinates.alpha <= coordinates.beta && coordinates.alpha <= coordinates.gamma)
            return a.getColour();
        else if (coordinates.beta <= coordinates.alpha && coordinates.beta <= coordinates.gamma)
            return b.getColour();
        else
            return c.getColour();
    }
};

export class GradientColourCalculator : public ColourCalculator
{

public:
    constexpr Colour calculateColour(const Vertex &a, const Vertex &b, const Vertex &c, const BarycentricCoordinate &coordinates) const override
    {
        return coordinates.alpha * a.getColour() + coordinates.beta * b.getColour() + coordinates.gamma * c.getColour();
    }
};