module;

#include <cmath>
#include <istream>
#include <ostream>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :math.matrix;

// ============================================================================
// Implementations
// ============================================================================

Vector3D Vector3D::operator+(const Vector3D &other) const
{
    return Vector3D(
        this->x() + other.x(),
        this->y() + other.y(),
        this->z() + other.z());
}

Vector3D Vector3D::operator-(const Vector3D &other) const
{
    return Vector3D(
        this->x() - other.x(),
        this->y() - other.y(),
        this->z() - other.z());
}

Vector3D Vector3D::operator*(double value) const
{
    return Vector3D(
        this->x() * value,
        this->y() * value,
        this->z() * value);
}

Vector3D Vector3D::operator/(double value) const
{
    return Vector3D(
        this->x() / value,
        this->y() / value,
        this->z() / value);
}

double Vector3D::dot(const Vector3D &other) const
{
    return this->x() * other.x() + this->y() * other.y() + this->z() * other.z();
}

Vector3D Vector3D::cross(const Vector3D &other) const
{
    return Vector3D(
        this->y() * other.z() - this->z() * other.y(),
        this->z() * other.x() - this->x() * other.z(), // This component has its sign changed.
        this->x() * other.y() - this->y() * other.x());
}

double Vector3D::magnitude() const
{
    return std::sqrt(this->dot(*this));
}

Vector3D Vector3D::normalize() const
{
    return (*this) / this->magnitude();
}

Vector3D::operator Vector2D() const
{
    return Vector2D{this->x(), this->y()};
}

Vector3D::operator Vector4D() const
{
    return Vector4D{this->x(), this->y(), this->z(), 1.};
}

Vector3D operator*(double value, const Vector3D &vector)
{
    return vector * value;
}

Vector3D &Vector3D::operator+=(const Vector3D &other)
{
    this->x() += other.x();
    this->y() += other.y();
    this->z() += other.z();

    return *this;
}

std::istream &operator>>(std::istream &is, Vector3D &v)
{
    is >> v.x() >> v.y() >> v.z();
    return is;
}

std::ostream &operator<<(std::ostream &out, const Vector3D &v)
{
    return out << "[ " << v.x() << " | " << v.y() << " | " << v.z() << " ]";
}

// ============================================================================
// EOF
// ============================================================================