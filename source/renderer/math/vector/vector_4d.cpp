module;

#include <ostream>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :math.matrix;

// ============================================================================
// Implementations
// ============================================================================

Vector4D Vector4D::operator+(const Vector4D &other) const
{
    return Vector4D(
        this->x() + other.x(), this->y() + other.y(),
        this->z() + other.z(), this->w() + other.w());
}

Vector4D Vector4D::operator-(const Vector4D &other) const
{
    return Vector4D(
        this->x() - other.x(), this->y() - other.y(),
        this->z() - other.z(), this->w() - other.w());
}

double Vector4D::dotProduct(const Vector4D &other) const
{
    return this->x() * other.x() +
           this->y() * other.y() +
           this->z() * other.z() +
           this->w() * other.w();
}

Vector4D::operator Vector3D() const
{
    return Vector3D{this->x(), this->y(), this->z()};
}

// Cross product is, strictly, defined only for 3 and 7 dimensions.

Vector4D operator*(
    const Matrix<double, 4, 4> &matrix, const Vector4D &vector)
{
    return matrix * vector.data;
}

std::ostream &operator<<(std::ostream &out, const Vector4D &v)
{
    return out << "[ " << v.x() << " | " << v.y() << " | " << v.z() << " | " << v.w() << " ]";
}

// ============================================================================
// EOF
// ============================================================================