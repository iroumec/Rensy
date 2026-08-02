module;

#include <random>
#include <vector>
#include <memory>
#include <cstdint>
#include <algorithm>

export module renderer:colour.generator;

import :structure.colour;

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

export class CircularColourGenerator : public ColourGenerator
{
    std::vector<std::shared_ptr<ColourGenerator>> generators;
    mutable std::size_t current = 0;

public:
    CircularColourGenerator(
        std::initializer_list<std::shared_ptr<ColourGenerator>> generators)
        : generators(generators) {}

    void addGenerator(std::shared_ptr<ColourGenerator> generator)
    {
        generators.push_back(std::move(generator));
    }

    Colour getColour() const override
    {
        if (generators.empty())
            throw std::runtime_error("No generators");

        Colour colour = generators[current]->getColour();

        current = (current + 1) % generators.size();

        return colour;
    }
};