module;

#include <ostream>

export module renderer:math.barycentric;

// ============================================================================
// Imports
// ============================================================================

import :math.geometry;
import :math.vector.vector_2d;

// ============================================================================
// Constans
// ============================================================================

constexpr double ONE_THIRD = 1.0 / 3.0;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export struct BarycentricCoordinate
{
    double alpha = ONE_THIRD;
    double beta = ONE_THIRD;
    double gamma = ONE_THIRD;

    constexpr bool isInsideTriangle() const
    {
        // If any of the coordinates are zero, then the point is outside the triangle.
        return alpha >= 0 && beta >= 0 && gamma >= 0;
    }

    static BarycentricCoordinate from(
        const Vector2D &a, const Vector2D &b, const Vector2D &c, const Vector2D &point)
    {
        double inversedArea = 1. / getSignedTriangleArea(a, b, c); // Total area.
        double alpha = getSignedTriangleArea(point, b, c) * inversedArea;
        double beta = getSignedTriangleArea(point, c, a) * inversedArea;
        double gamma = getSignedTriangleArea(point, a, b) * inversedArea;
        return {alpha, beta, gamma};
    }

    friend std::ostream &operator<<(
        std::ostream &out, const BarycentricCoordinate &coordinates)
    {
        return out << "[ " << coordinates.alpha << " | " << coordinates.beta
                   << " | " << coordinates.gamma << " ]";
    }
};

// ============================================================================
// EOF
// ============================================================================
