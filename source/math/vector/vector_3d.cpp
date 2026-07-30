module;

#include <istream>
#include <ostream>

module vector;

// ============================================================================
// Imports
// ============================================================================

import matrix;

// ============================================================================
// Implementations
// ============================================================================

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

Vector3D::operator Vector2D() const
{
    return Vector2D{this->x(), this->y()};
}

Vector3D::operator Vector4D() const
{
    return Vector4D{this->x(), this->y(), this->z(), 1.};
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