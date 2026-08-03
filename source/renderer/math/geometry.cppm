module;

#include <cmath>
#include <array>
#include <cassert>
#include <iostream>
#include <algorithm>

export module renderer:math.geometry;

import :math.vector.vector_3d;
import :math.vector.vector_2d;

// Given an Y value, returns an X value.
export double interpolateX(Vector3D a, Vector3D b, double y)
{
    double t = (y - a.y()) / (b.y() - a.y());
    t = std::clamp(t, 0.0, 1.0);        // So it doesn't go out of the range.
    return t * (b.x() - a.x()) + a.x(); // Some triangles look better rounding, while others look worse. THERE IS NO CORRECT ROUNDING.
}

// Given an X value, returns an Y value.
export double interpolateY(Vector3D a, Vector3D b, double x)
{
    double t = (x - a.x()) / (b.x() - a.x());
    t = std::clamp(t, 0.0, 1.0);
    return t * (b.y() - a.y()) + a.y(); // Some triangles look better rounding, while others look worse. THERE IS NO CORRECT ROUNDING.
}

export constexpr double getSignedTriangleArea(const Vector2D &a, const Vector2D &b, const Vector2D &c)
{
    // See documentation/drawings/boundingBoxRasterization.excalidraw.
    return .5 * ((b.y() - a.y()) * (b.x() + a.x()) + (c.y() - b.y()) * (c.x() + b.x()) + (a.y() - c.y()) * (a.x() + c.x()));
}