module;

#include <random>
#include <vector>
#include <memory>
#include <cstdint>
#include <ostream>
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

    constexpr Colour(
        std::uint8_t r = 0,
        std::uint8_t g = 0,
        std::uint8_t b = 0,
        std::uint8_t a = 255)
        : r{r}, g{g}, b{b}, a{a} {}

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

    Colour blend(const Colour &colour, double intensity) const
    {
        intensity = std::clamp(intensity, 0.0, 1.0);

        return Colour{
            static_cast<uint8_t>(r * (1 - intensity) + colour.r * intensity),
            static_cast<uint8_t>(g * (1 - intensity) + colour.g * intensity),
            static_cast<uint8_t>(b * (1 - intensity) + colour.b * intensity),
            a};
    }

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

    Colour &operator=(const Colour &) = default;

    friend std::ostream &operator<<(std::ostream &out, const Colour &colour)
    {
        out << "R: "
            << static_cast<int>(colour.r)
            << ", G: "
            << static_cast<int>(colour.g)
            << ", B: "
            << static_cast<int>(colour.b)
            << ", A: "
            << static_cast<int>(colour.a) << '\n';

        return out;
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
export constexpr Colour darkGray = {64, 64, 64, 255};
export constexpr Colour gray = {169, 169, 169, 255};
export constexpr Colour lightGray = {211, 211, 211, 255};
export constexpr Colour black = {0, 0, 0, 255};