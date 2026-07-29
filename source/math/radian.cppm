module;

#include <numbers>

export module radian;

inline constexpr double degreesToRadians(double degrees)
{
    return degrees * std::numbers::pi / 180.0;
}

export class Radian
{
    const double radians;

    constexpr Radian(double radians)
        : radians{radians} {}

public:
    constexpr Radian()
        : radians{0.0}
    {
    }

    static constexpr Radian fromDegrees(double degrees)
    {
        return Radian(degreesToRadians(degrees));
    }

    static constexpr Radian fromRadians(double radians)
    {
        return Radian(radians);
    }

    double constexpr operator()() const
    {
        return this->radians;
    }
};