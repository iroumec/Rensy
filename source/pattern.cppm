module;

#include <cmath>
#include <memory>

export module pattern;

import barycentric;

export class Pattern
{

public:
    virtual ~Pattern() = default;

    virtual constexpr bool isValid(const BarycentricCoordinate &coordinates) const = 0;
};

export class BorderPattern : public Pattern
{
    const double epsilon; // It's not recommended a value smaller than 0.04.

public:
    BorderPattern(double epsilon = 4e-2) : epsilon(epsilon) {}

    constexpr bool isValid(const BarycentricCoordinate &coordinates) const override
    {

        return std::abs(coordinates.alpha) < epsilon ||
               std::abs(coordinates.beta) < epsilon ||
               std::abs(coordinates.gamma) < epsilon;
    }
};

export class CenterPattern : public Pattern
{

    const double epsilon; // It's not recommended a value smaller than 0.1.

public:
    CenterPattern(double epsilon = 1e-1) : epsilon(epsilon) {}

    constexpr bool isValid(const BarycentricCoordinate &coordinates) const override
    {

        return std::abs(coordinates.alpha) > epsilon &&
               std::abs(coordinates.beta) > epsilon &&
               std::abs(coordinates.gamma) > epsilon;
    }
};