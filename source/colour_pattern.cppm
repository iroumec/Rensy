module;

#include <cmath>

export module colour_pattern;

import colour;
import barycentric;

// See documentation/drawings/colourPatterns.excalidraw.
export class ColourPattern
{

public:
    virtual ~ColourPattern() = default;

    virtual constexpr Colour adjustColour(const Colour &colour, const BarycentricCoordinate &coordinates) const = 0;
};

export class BorderColourPattern : public ColourPattern
{

public:
    constexpr Colour adjustColour(const Colour &colour, const BarycentricCoordinate &coordinates) const override
    {
        double intensity = std::pow(coordinates.alpha, 2) + std::pow(coordinates.beta, 2) + std::pow(coordinates.gamma, 2);

        return colour * intensity;
    }
};

export class CenterColourPattern : public ColourPattern
{

public:
    constexpr Colour adjustColour(const Colour &colour, const BarycentricCoordinate &coordinates) const override
    {
        double intensity = (std::pow(coordinates.alpha, 2) + std::pow(coordinates.beta, 2) + std::pow(coordinates.gamma, 2)) * 3;

        return colour * (1 / intensity);
    }
};