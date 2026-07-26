module;

export module barycentric;

import vector;

export struct BarycentricCoordinate
{
    double alpha = 0;
    double beta = 0;
    double gamma = 0;
};

inline constexpr double getSignedTriangleArea(const Vector2D &a, const Vector2D &b, const Vector2D &c)
{
    // See documentation/drawings/boundingBoxRasterization.excalidraw.
    return .5 * ((b.y - a.y) * (b.x + a.x) + (c.y - b.y) * (c.x + b.x) + (a.y - c.y) * (a.x + c.x));
}

export inline constexpr BarycentricCoordinate getBarycentricCoordinates(
    const Vector2D &a, const Vector2D &b, const Vector2D &c, const Vector2D &point)
{
    double totalArea = getSignedTriangleArea(a, b, c);
    double alpha = getSignedTriangleArea(point, b, c) / totalArea;
    double beta = getSignedTriangleArea(point, c, a) / totalArea;
    double gamma = getSignedTriangleArea(point, a, b) / totalArea;
    return {alpha, beta, gamma};
}