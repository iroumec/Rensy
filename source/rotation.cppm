module;

#include <numbers>

export module rotation;

import vector;

constexpr double degreesToRadians(double degrees)
{
    return degrees * std::numbers::pi / 180.0;
}

export struct Rotation
{

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    constexpr Vector3D apply(const Vector3D &vector) const
    {

        Vector3D result = vector;
        result = (x > 0.0) ? result.rotateInX(degreesToRadians(x)) : result;
        result = (y > 0.0) ? result.rotateInY(degreesToRadians(y)) : result;
        result = (z > 0.0) ? result.rotateInZ(degreesToRadians(z)) : result;

        return result;
    }
};