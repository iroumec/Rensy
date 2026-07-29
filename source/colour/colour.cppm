module;

#include <random>
#include <vector>
#include <memory>
#include <cstdint>
#include <algorithm>

export module colour;

import tgaimage;

// BGRA.
export struct Colour
{
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t a;

    // --------------------------------------------------------------------- //
    // RANDOM GENERATION
    // --------------------------------------------------------------------- //

    static Colour random()
    {
        static std::mt19937 rng{std::random_device{}()};
        static std::uniform_int_distribution<int> dist{0, 255};

        return {
            static_cast<std::uint8_t>(dist(rng)),
            static_cast<std::uint8_t>(dist(rng)),
            static_cast<std::uint8_t>(dist(rng)),
            255};
    }

    // --------------------------------------------------------------------- //
    //
    // --------------------------------------------------------------------- //

    Colour adjustTransparency(double multiplier) const
    {
        return Colour{
            r, g, b,
            static_cast<std::uint8_t>(std::clamp(a * multiplier, 0.0, 255.0))};
    }

    // --------------------------------------------------------------------- //
    // * OPERATOR
    // --------------------------------------------------------------------- //

    Colour operator*(double adjust) const
    {
        // TODO: hacer clamp sobre adjust en lugar de sobre el color.

        return Colour{
            static_cast<std::uint8_t>(std::clamp(r * adjust, 0.0, 255.0)),
            static_cast<std::uint8_t>(std::clamp(g * adjust, 0.0, 255.0)),
            static_cast<std::uint8_t>(std::clamp(b * adjust, 0.0, 255.0)),
            a};
    }

    friend Colour operator*(double adjust, const Colour &colour)
    {
        return colour * adjust;
    }

    // --------------------------------------------------------------------- //
    // + OPERATOR
    // --------------------------------------------------------------------- //

    Colour operator+(const Colour &other) const
    {
        return Colour{
            static_cast<std::uint8_t>(std::clamp(r + other.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(g + other.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(b + other.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(a + other.a, 0, 255)),
        };
    }

    operator TGAColour() const
    {
        return TGAColour{{b, g, r, a}};
    }
};

// BGRA.
export constexpr Colour white = {255, 255, 255, 255};
export constexpr Colour green = {0, 255, 0, 255};
export constexpr Colour blue = {0, 0, 255, 255};
export constexpr Colour red = {255, 0, 0, 255};
export constexpr Colour cyan = {0, 255, 255, 255};
export constexpr Colour yellow = {255, 255, 0, 255};
export constexpr Colour magenta = {255, 0, 255, 255};
export constexpr Colour orange = {255, 165, 0, 255};
export constexpr Colour purple = {128, 0, 128, 255};