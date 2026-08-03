module;

#include <ostream>

export module renderer:math.vector.vector_2d;

// ============================================================================
// Imports
// ============================================================================

import :math.matrix;

// ============================================================================
// Forward Declarations
// ============================================================================

class Vector3D;

// ============================================================================
// Declarations
// ============================================================================

export class Vector2D
{
    Matrix<double, 2, 1> data;

public:
    Vector2D(const Matrix<double, 2, 1> matrix)
        : data{matrix} {}

    Vector2D(double x = 0.0, double y = 0.0)
        : data{x, y} {}

    constexpr double x() const { return data[0, 0]; }
    constexpr double y() const { return data[1, 0]; }
    constexpr double &x() { return data[0, 0]; }
    constexpr double &y() { return data[1, 0]; }

    Vector2D operator+(const Vector2D &other) const;

    Vector2D operator-(const Vector2D &other) const;

    double dotProduct(const Vector2D &other) const;

    // Cross product is, strictly, not defined for 2D vectors.

    operator Vector3D() const;

    Vector2D &operator=(const Vector2D &) = default;

    friend std::ostream &operator<<(std::ostream &out, const Vector2D &v);
};

// ============================================================================
// EOF
// ============================================================================