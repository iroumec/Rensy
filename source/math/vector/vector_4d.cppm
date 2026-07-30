module;

#include <ostream>

export module vector:vector_4d;

// ============================================================================
// Imports
// ============================================================================

import matrix;

// ============================================================================
// Forward Declarations
// ============================================================================

class Vector3D;

// ============================================================================
// Declarations
// ============================================================================

export class Vector4D
{
    Matrix<double, 4, 1> data;

public:
    Vector4D(const Matrix<double, 4, 1> matrix)
        : data{matrix} {}

    Vector4D(double x, double y, double z, double w)
        : data{x, y, z, w} {}

    constexpr double x() const { return data[0, 0]; }
    constexpr double y() const { return data[1, 0]; }
    constexpr double z() const { return data[2, 0]; }
    constexpr double w() const { return data[3, 0]; }
    constexpr double &x() { return data[0, 0]; }
    constexpr double &y() { return data[1, 0]; }
    constexpr double &z() { return data[2, 0]; }
    constexpr double &w() { return data[3, 0]; }

    Vector4D operator+(const Vector4D &other) const;

    Vector4D operator-(const Vector4D &other) const;

    double dotProduct(const Vector4D &other) const;

    operator Vector3D() const;

    // Cross product is, strictly, defined only for 3 and 7 dimensions.

    friend Vector4D operator*(
        const Matrix<double, 4, 4> &matrix, const Vector4D &vector);

    friend std::ostream &operator<<(std::ostream &out, const Vector4D &v);
};

// ============================================================================
// EOF
// ============================================================================