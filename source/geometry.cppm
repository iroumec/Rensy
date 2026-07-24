module;

#include <cmath>
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

// Operador de impresión para vec3
export inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z << ' ';
}