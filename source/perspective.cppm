module;

#include <stdexcept>

export module perspective;

import vector;

export constexpr Vector3D wPerspectiveDivide(const Vector4D &vector)
{
    const double w = vector.w();

    if (w == 0.0)
        throw std::runtime_error("Perspective divide by zero");

    return Vector3D{
        vector.x() / w,
        vector.y() / w,
        vector.z() / w};
}

export constexpr Vector3D constantPerspectiveDivide(const Vector4D &vector)
{
    constexpr unsigned c = 3;

    if (c == 0)
        throw std::runtime_error("Perspective divide by zero");

    const double w = 1 - vector.z() / c;

    return Vector3D{
        vector.x() / w,
        vector.y() / w,
        vector.z() / w};
}