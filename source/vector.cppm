module;

#include <array>
#include <cmath>
#include <utility>
#include <iostream>

export module vector;

import matrix;

export class Vector2D;
export class Vector3D;
export class Vector4D;

class Vector2D
{
public:
    double x, y;

    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    constexpr Vector2D operator+(const Vector2D &other) const
    {
        return Vector2D(this->x + other.x, this->y + other.y);
    }

    constexpr Vector2D operator-(const Vector2D &other) const
    {
        return Vector2D(this->x - other.x, this->y - other.y);
    }

    constexpr double dotProduct(const Vector2D &other) const
    {
        return this->x * other.x + this->y * other.y;
    }

    // Cross product is, strictly, not defined for 2D vectors.

    constexpr operator Vector3D() const;
};

export std::ostream &operator<<(std::ostream &out, const Vector2D &v)
{
    return out << v.x << ' ' << v.y << ' ';
}

class Vector3D
{
    Matrix<double, 3, 1> data;

public:
    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0) : data{x, y, z} {}
    Vector3D(const Matrix<double, 3, 1> matrix) : data{matrix} {}

    constexpr double x() const { return data[0, 0]; }
    constexpr double y() const { return data[1, 0]; }
    constexpr double z() const { return data[2, 0]; }
    constexpr double &x() { return data[0, 0]; }
    constexpr double &y() { return data[1, 0]; }
    constexpr double &z() { return data[2, 0]; }

    constexpr double dot(const Vector3D &other) const
    {
        return this->x() * other.x() + this->y() * other.y() + this->z() * other.z();
    }

    constexpr Vector3D cross(const Vector3D &other) const
    {
        return Vector3D(
            this->y() * other.z() - this->z() * other.y(),
            this->z() * other.x() - this->x() * other.z(), // This component has its sign changed.
            this->x() * other.y() - this->y() * other.x());
    }

    constexpr Vector3D rotateInX(double radians) const
    {
        Matrix<double, 3, 3> Rx =
            {
                {1, 0, 0},
                {0, std::cos(radians), -std::sin(radians)},
                {0, std::sin(radians), std::cos(radians)}};

        return Vector3D(Rx * this->data);
    }

    constexpr Vector3D rotateInY(double radians) const
    {
        Matrix<double, 3, 3> Ry =
            {
                {std::cos(radians), 0, std::sin(radians)},
                {0, 1, 0},
                {-std::sin(radians), 0, std::cos(radians)}};

        return Vector3D(Ry * this->data);
    }

    constexpr Vector3D rotateInZ(double radians) const
    {
        Matrix<double, 3, 3> Rz =
            {
                {std::cos(radians), -std::sin(radians), 0},
                {std::sin(radians), std::cos(radians), 0},
                {0, 0, 1},
            };

        return Vector3D(Rz * this->data);
    }

    constexpr operator Vector2D() const;

    friend std::istream &operator>>(std::istream &is, Vector3D &v)
    {
        is >> v.x() >> v.y() >> v.z();
        return is;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector3D &v)
    {
        return out << v.x() << ' ' << v.y() << ' ' << v.z() << ' ';
    }
};

class Vector4D
{
public:
    double x, y, z, w;

    Vector4D(double x = 0.0, double y = 0.0, double z = 0.0, double w = 0.0) : x(x), y(y), z(z), w(w) {}

    constexpr Vector4D operator+(const Vector4D &other) const
    {
        return Vector4D(
            this->x + other.x, this->y + other.y,
            this->z + other.z, this->w + other.w);
    }

    constexpr Vector4D operator-(const Vector4D &other) const
    {
        return Vector4D(
            this->x - other.x, this->y - other.y,
            this->z - other.z, this->w - other.w);
    }

    constexpr double dotProduct(const Vector4D &other) const
    {
        return this->x * other.x +
               this->y * other.y +
               this->z * other.z +
               this->w * other.w;
    }

    // Cross product is, strictly, defined only for 3 and 7 dimensions.
};

std::ostream &operator<<(std::ostream &out, const Vector4D &v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << ' ';
}

export std::array<Vector3D, 3> orderByAscendingAxisY(Vector3D a, Vector3D b, Vector3D c)
{
    if (a.y() > b.y())
        std::swap(a, b);
    if (a.y() > c.y())
        std::swap(a, c);
    if (b.y() > c.y())
        std::swap(b, c);

    return {a, b, c};
}

constexpr Vector2D::operator Vector3D() const
{
    return Vector3D{x, y, 0.0};
}

constexpr Vector3D::operator Vector2D() const
{
    return Vector2D{this->x(), this->y()};
}