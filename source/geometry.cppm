module;

#include <cmath>
#include <array>
#include <cassert>
#include <iostream>

export module geometry;

import vector;

export inline float clamp(float value, float min, float max)
{
    return std::min(std::max(value, min), max);
}

// Given an Y value, returns an X value.
export inline float interpolateX(Vector3D a, Vector3D b, float y)
{
    float t = (y - a.y()) / static_cast<float>(b.y() - a.y());
    t = clamp(t, 0.0, 1.0);             // So it doesn't go out of the range.
    return t * (b.x() - a.x()) + a.x(); // Some triangles look better rounding, while others look worse. THERE IS NO CORRECT ROUNDING.
}

// Given an X value, returns an Y value.
export inline float interpolateY(Vector3D a, Vector3D b, float x)
{
    float t = (x - a.x()) / static_cast<float>(b.x() - a.x());
    t = clamp(t, 0.0, 1.0);
    return t * (b.y() - a.y()) + a.y(); // Some triangles look better rounding, while others look worse. THERE IS NO CORRECT ROUNDING.
}