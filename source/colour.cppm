module;

#include <random>
#include <cstdint>

export module colour;

import tgaimage;

// BGRA.
export struct Colour
{
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t a;

    operator TGAColour() const
    {
        return TGAColour{{b, g, r, a}};
    }
};

export class ColourGenerator
{
public:
    virtual ~ColourGenerator() = default;

    virtual Colour getColour() const = 0;

    Colour operator()() const
    {
        return getColour();
    }
};

export class StaticColourGenerator : public ColourGenerator
{
    Colour colour;

public:
    StaticColourGenerator(Colour colour)
        : colour{colour}
    {
    }

    Colour getColour() const override
    {
        return colour;
    }
};

export class RandomColourGenerator : public ColourGenerator
{
    mutable std::mt19937 generator{std::random_device{}()};
    mutable std::uniform_int_distribution<int> distribution{0, 255};

public:
    RandomColourGenerator()
        : generator{std::random_device{}()}
    {
    }

    RandomColourGenerator(unsigned seed)
        : generator{seed}
    {
    }

    Colour getColour() const override
    {
        return Colour{
            static_cast<std::uint8_t>(distribution(generator)),
            static_cast<std::uint8_t>(distribution(generator)),
            static_cast<std::uint8_t>(distribution(generator)),
            255};
    }
};

// BGRA.
export constexpr Colour white = {255, 255, 255, 255};
export constexpr Colour green = {0, 255, 0, 255};
export constexpr Colour red = {0, 0, 255, 255};
export constexpr Colour blue = {255, 0, 0, 255};
export constexpr Colour yellow = {0, 255, 255, 255};
export constexpr Colour cyan = {255, 255, 0, 255};
export constexpr Colour magenta = {255, 0, 255, 255};
export constexpr Colour orange = {0, 165, 255, 255};
export constexpr Colour purple = {128, 0, 128, 255};