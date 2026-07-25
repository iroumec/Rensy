module;

#include <cmath>
#include <array>
#include <cassert>
#include <iostream>

export module geometry;

// 1. Plantilla genérica para cualquier dimensión (vec<2>, vec<4>, etc.)
// It is used to represent both points and vectors.
export template <unsigned n>
struct vec
{
    double data[n] = {0};

    double &operator[](const unsigned i)
    {
        assert(i >= 0 && i < n);
        return data[i];
    }

    double operator[](const unsigned i) const
    {
        assert(i >= 0 && i < n);
        return data[i];
    }
};

// Operador de impresión para la plantilla genérica
export template <unsigned n>
std::ostream &operator<<(std::ostream &out, const vec<n> &v)
{
    for (int i = 0; i < n; ++i)
        out << v[i] << ' ';
    return out;
}

export struct vec2
{
    double x = 0;
    double y = 0;

    double &operator[](const int i)
    {
        assert(i >= 0 && i < 2);
        return i ? y : x;
    }

    double operator[](const int i) const
    {
        assert(i >= 0 && i < 2);
        return i ? y : x;
    }
};

export struct vec3
{
    double x = 0;
    double y = 0;
    double z = 0;

    vec3() = default;

    vec3(double x, double y, double z)
        : x{x}, y{y}, z{z}
    {
    }

    vec3(const vec2 &vector2D)
        : x{vector2D.x}, y{vector2D.y}, z{0}
    {
    }

    double &operator[](const int i)
    {
        assert(i >= 0 && i < 3);
        return i ? (i == 1 ? y : z) : x;
    }

    double operator[](const int i) const
    {
        assert(i >= 0 && i < 3);
        return i ? (i == 1 ? y : z) : x;
    }
};

export struct BarycentricCoordinate
{
    double alpha = 0;
    double beta = 0;
    double gamma = 0;
};

export inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z << ' ';
}

export inline std::ostream &operator<<(std::ostream &out, const vec2 &v)
{
    return out << v.x << ' ' << v.y << ' ';
}

export std::array<vec3, 3> orderByAscendingAxisY(vec3 a, vec3 b, vec3 c)
{
    if (a.y > b.y)
        std::swap(a, b);
    if (a.y > c.y)
        std::swap(a, c);
    if (b.y > c.y)
        std::swap(b, c);

    return {a, b, c};
}

export inline float clamp(float value, float min, float max)
{
    return std::min(std::max(value, min), max);
}

// Given an Y value, returns an X value.
export inline float interpolateX(vec3 a, vec3 b, float y)
{
    float t = (y - a.y) / static_cast<float>(b.y - a.y);
    t = clamp(t, 0.0, 1.0);       // So it doesn't go out of the range.
    return t * (b.x - a.x) + a.x; // Some triangles look better rounding, while others look worse. THERE IS NO CORRECT ROUNDING.
}

// Given an X value, returns an Y value.
export inline float interpolateY(vec3 a, vec3 b, float x)
{
    float t = (x - a.x) / static_cast<float>(b.x - a.x);
    t = clamp(t, 0.0, 1.0);
    return t * (b.y - a.y) + a.y; // Some triangles look better rounding, while others look worse. THERE IS NO CORRECT ROUNDING.
}

export inline double getSignedTriangleArea(vec3 a, vec3 b, vec3 c)
{
    // See documentation/drawings/boundingBoxRasterization.excalidraw.
    return .5 * ((b.y - a.y) * (b.x + a.x) + (c.y - b.y) * (c.x + b.x) + (a.y - c.y) * (a.x + c.x));
}

export inline BarycentricCoordinate getBarycentricCoordinates(vec3 a, vec3 b, vec3 c, vec3 point)
{
    double totalArea = getSignedTriangleArea(a, b, c);
    double alpha = getSignedTriangleArea(point, b, c) / totalArea;
    double beta = getSignedTriangleArea(point, c, a) / totalArea;
    double gamma = getSignedTriangleArea(point, a, b) / totalArea;
    return {alpha, beta, gamma};
}

// Viewport transform.
export inline vec3 projectVector(vec3 vector, unsigned width, unsigned height)
{
    // First, ortographics projection -> Z axis is discard.
    // Second, since the input models are scaled to have fir in the [-1.1]^3 world coordinates,
    // the vector is scaled to span the entire screen.
    vec3 out;
    out.x = (vector.x + 1.) * width / 2;
    out.y = (vector.y + 1.) * height / 2;
    out.z = (vector.z + 1.) * 255. / 2; // Here we save the colours.

    return out;
}