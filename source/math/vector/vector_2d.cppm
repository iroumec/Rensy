module;

#include <ostream>

export module vector:vector_2d;

// ============================================================================
// Forward Declarations
// ============================================================================

class Vector3D;

// ============================================================================
// Declarations
// ============================================================================

export class Vector2D
{
public:
    double x, y;

    Vector2D() = default;

    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Vector2D operator+(const Vector2D &other) const;

    Vector2D operator-(const Vector2D &other) const;

    double dotProduct(const Vector2D &other) const;

    // Cross product is, strictly, not defined for 2D vectors.

    operator Vector3D() const;

    Vector2D operator=(const Vector2D &other) const;

    friend std::ostream &operator<<(std::ostream &out, const Vector2D &v);
};

// ============================================================================
// EOF
// ============================================================================