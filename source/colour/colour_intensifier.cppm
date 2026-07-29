module;

#include <cmath>

export module colour_intensifier;

import colour;
import vertex;
import barycentric;

// See documentation/drawings/colourPatterns.excalidraw.
export class ColourIntensifier
{

public:
    virtual ~ColourIntensifier() = default;

    virtual constexpr Colour adjustColour(
        const Colour &colour, const Vertex &a, const Vertex &b,
        const Vertex &c, const BarycentricCoordinate &coordinates) const = 0;
};

export class BorderColourIntensifier : public ColourIntensifier
{

public:
    constexpr Colour adjustColour(
        const Colour &colour, const Vertex &a, const Vertex &b,
        const Vertex &c, const BarycentricCoordinate &coordinates) const override
    {
        double intensity = std::pow(coordinates.alpha, 2) + std::pow(coordinates.beta, 2) + std::pow(coordinates.gamma, 2);

        return colour * intensity;
    }
};

export class CenterColourIntensifier : public ColourIntensifier
{

public:
    constexpr Colour adjustColour(
        const Colour &colour, const Vertex &a, const Vertex &b,
        const Vertex &c, const BarycentricCoordinate &coordinates) const override
    {
        double intensity = (std::pow(coordinates.alpha, 2) + std::pow(coordinates.beta, 2) + std::pow(coordinates.gamma, 2)) * 3;

        return colour * (1 / intensity);
    }
};

export class DepthColourIntensifier : public ColourIntensifier
{

public:
    constexpr Colour adjustColour(
        const Colour &colour, const Vertex &a, const Vertex &b,
        const Vertex &c, const BarycentricCoordinate &coordinates) const override
    {
        double minZ = std::min(a.z(), std::min(b.z(), c.z()));
        double maxZ = std::max(a.z(), std::max(b.z(), c.z()));

        double currentDepth = coordinates.alpha * a.z() + coordinates.beta * b.z() + coordinates.gamma * c.z();

        double intensity = 1.0;

        if (maxZ != minZ)
            intensity = (currentDepth - minZ) / (maxZ - minZ);

        return colour * intensity;
    }
};