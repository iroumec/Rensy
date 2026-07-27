module;

#include <cmath>
#include <array>
#include <cassert>
#include <iostream>

export module geometry;

import vector;

export inline double clamp(double value, double min, double max)
{
    return std::min(std::max(value, min), max);
}

// Given an Y value, returns an X value.
export inline double interpolateX(Vector3D a, Vector3D b, double y)
{
    double t = (y - a.y()) / (b.y() - a.y());
    t = clamp(t, 0.0, 1.0);             // So it doesn't go out of the range.
    return t * (b.x() - a.x()) + a.x(); // Some triangles look better rounding, while others look worse. THERE IS NO CORRECT ROUNDING.
}

// Given an X value, returns an Y value.
export inline double interpolateY(Vector3D a, Vector3D b, double x)
{
    double t = (x - a.x()) / (b.x() - a.x());
    t = clamp(t, 0.0, 1.0);
    return t * (b.y() - a.y()) + a.y(); // Some triangles look better rounding, while others look worse. THERE IS NO CORRECT ROUNDING.
}