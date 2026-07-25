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

// 2. Estructura dedicada para 3D (Estructura propia en lugar de especialización)
export struct vec3
{
    double x = 0;
    double y = 0;
    double z = 0;

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

export inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z << ' ';
}

export inline std::ostream &operator<<(std::ostream &out, const vec2 &v)
{
    return out << v.x << ' ' << v.y << ' ';
}

export std::array<vec2, 3> orderByAscendingAxisY(vec2 a, vec2 b, vec2 c)
{
    if (a.y > b.y)
        std::swap(a, b);
    if (a.y > c.y)
        std::swap(a, c);
    if (b.y > c.y)
        std::swap(b, c);

    return {a, b, c};
}

export float clamp(float value, float min, float max)
{
    return std::min(std::max(value, min), max);
}

// Given an Y value, returns an X value.
export float interpolateX(vec2 a, vec2 b, float y)
{
    float t = (y - a.y) / static_cast<float>(b.y - a.y);
    t = clamp(t, 0.0, 1.0);       // So it doesn't go out of the range.
    return t * (b.x - a.x) + a.x; // Some triangles look better rounding, while others look worse. THERE IS NO CORRECT ROUNDING.
}

// Given an X value, returns an Y value.
export float interpolateY(vec2 a, vec2 b, float x)
{
    float t = (x - a.x) / static_cast<float>(b.x - a.x);
    t = clamp(t, 0.0, 1.0);
    return t * (b.y - a.y) + a.y; // Some triangles look better rounding, while others look worse. THERE IS NO CORRECT ROUNDING.
}

export double getSignedTriangleArea(vec2 a, vec2 b, vec2 c)
{
    // See documentation/drawings/boundingBoxRasterization.excalidraw.
    return .5 * ((b.y - a.y) * (b.x + a.x) + (c.y - b.y) * (c.x + b.x) + (a.y - c.y) * (a.x + c.x));
}

export vec3 getBarycentricCoordinates(vec2 a, vec2 b, vec2 c, vec2 point)
{
    double totalArea = getSignedTriangleArea(a, b, c);
    double alpha = getSignedTriangleArea(point, b, c) / totalArea;
    double beta = getSignedTriangleArea(point, c, a) / totalArea;
    double gamma = getSignedTriangleArea(point, a, b) / totalArea;
    return vec3{alpha, beta, gamma};
}