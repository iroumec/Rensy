module;

#include <array>
#include <ostream>
#include <utility>

export module vector;

export class Vector2D;
export class Vector3D;
export class Vector4D;

class Vector2D
{
public:
    double x, y;

    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Vector2D operator+(const Vector2D &other) const
    {
        return Vector2D(this->x + other.x, this->y + other.y);
    }

    Vector2D operator-(const Vector2D &other) const
    {
        return Vector2D(this->x - other.x, this->y - other.y);
    }

    double dotProduct(const Vector2D &other) const
    {
        return this->x * other.x + this->y * other.y;
    }

    // Cross product is, strictly, not defined for 2D vectors.

    operator Vector3D() const;
};

export std::ostream &operator<<(std::ostream &out, const Vector2D &v)
{
    return out << v.x << ' ' << v.y << ' ';
}

class Vector3D
{
public:
    double x, y, z;

    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

    Vector3D operator+(const Vector3D &other) const
    {
        return Vector3D(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    Vector3D operator-(const Vector3D &other) const
    {
        return Vector3D(this->x - other.x, this->y - other.y, this->z - other.z);
    }

    double dotProduct(const Vector3D &other) const
    {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }

    Vector3D crossProduct(const Vector3D &other) const
    {
        return Vector3D(
            this->y * other.z - this->z * other.y,
            this->z * other.x - this->x * other.z, // This component has its sign changed.
            this->x * other.y - this->y * other.x);
    }

    operator Vector2D() const;
};

export std::ostream &operator<<(std::ostream &out, const Vector3D &v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z << ' ';
}

class Vector4D
{
public:
    double x, y, z, w;

    Vector4D(double x = 0.0, double y = 0.0, double z = 0.0, double w = 0.0) : x(x), y(y), z(z), w(w) {}

    Vector4D operator+(const Vector4D &other) const
    {
        return Vector4D(
            this->x + other.x, this->y + other.y,
            this->z + other.z, this->w + other.w);
    }

    Vector4D operator-(const Vector4D &other) const
    {
        return Vector4D(
            this->x - other.x, this->y - other.y,
            this->z - other.z, this->w - other.w);
    }

    double dotProduct(const Vector4D &other) const
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
    if (a.y > b.y)
        std::swap(a, b);
    if (a.y > c.y)
        std::swap(a, c);
    if (b.y > c.y)
        std::swap(b, c);

    return {a, b, c};
}

Vector2D::operator Vector3D() const
{
    return Vector3D{x, y, 0.0};
}

Vector3D::operator Vector2D() const
{
    return Vector2D{x, y};
}