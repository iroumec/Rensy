module;

#include <istream>
#include <ostream>

export module vector:vector_3d;

// ============================================================================
// Imports
// ============================================================================

import matrix;

// ============================================================================
// Forward Declarations
// ============================================================================

class Vector2D;
class Vector4D;

// ============================================================================
// Declarations
// ============================================================================

export class Vector3D
{
    Matrix<double, 3, 1> data;

public:
    Vector3D(const Matrix<double, 3, 1> matrix)
        : data{matrix} {}

    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0)
        : data{x, y, z} {}

    constexpr double x() const { return data[0, 0]; }
    constexpr double y() const { return data[1, 0]; }
    constexpr double z() const { return data[2, 0]; }
    constexpr double &x() { return data[0, 0]; }
    constexpr double &y() { return data[1, 0]; }
    constexpr double &z() { return data[2, 0]; }

    double dot(const Vector3D &other) const;

    Vector3D cross(const Vector3D &other) const;

    operator Vector2D() const;

    operator Vector4D() const;

    friend std::istream &operator>>(std::istream &is, Vector3D &v);

    friend std::ostream &operator<<(std::ostream &out, const Vector3D &v);
};

// ============================================================================
// EOF
// ============================================================================