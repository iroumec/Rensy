module;

#include <ostream>

module vector;

// ============================================================================
// Implementations
// ============================================================================

Vector2D Vector2D::operator+(const Vector2D &other) const
{
    return Vector2D(this->x + other.x, this->y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D &other) const
{
    return Vector2D(this->x - other.x, this->y - other.y);
}

double Vector2D::dotProduct(const Vector2D &other) const
{
    return this->x * other.x + this->y * other.y;
}

Vector2D::operator Vector3D() const
{
    return Vector3D{x, y, 0.0};
}

std::ostream &operator<<(std::ostream &out, const Vector2D &v)
{
    return out << v.x << ' ' << v.y << ' ';
}

// ============================================================================
// EOF
// ============================================================================