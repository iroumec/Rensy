module;

#include <ostream>

export module renderer:math.barycentric;

import :math.vector.vector_2d;

export struct BarycentricCoordinate
{
    double alpha = 0;
    double beta = 0;
    double gamma = 0;

    constexpr bool isInsideTriangle() const
    {
        // If any of the coordinates are zero, then the point is outside the triangle.
        return alpha >= 0 && beta >= 0 && gamma >= 0;
    }
};

inline constexpr double getSignedTriangleArea(const Vector2D &a, const Vector2D &b, const Vector2D &c)
{
    // See documentation/drawings/boundingBoxRasterization.excalidraw.
    return .5 * ((b.y - a.y) * (b.x + a.x) + (c.y - b.y) * (c.x + b.x) + (a.y - c.y) * (a.x + c.x));
}

export inline constexpr BarycentricCoordinate getBarycentricCoordinates(
    const Vector2D &a, const Vector2D &b, const Vector2D &c, const Vector2D &point)
{

    double inversedArea = 1. / getSignedTriangleArea(a, b, c); // Total area.
    double alpha = getSignedTriangleArea(point, b, c) * inversedArea;
    double beta = getSignedTriangleArea(point, c, a) * inversedArea;
    double gamma = getSignedTriangleArea(point, a, b) * inversedArea;
    return {alpha, beta, gamma};
}

export std::ostream &operator<<(std::ostream &out, const BarycentricCoordinate &coordinates)
{
    return out << "[ " << coordinates.alpha << " | " << coordinates.beta << " | " << coordinates.gamma << " ]";
}