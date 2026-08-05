module;

#include <cmath>
#include <memory>
#include <vector>
#include <algorithm>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :math.bbox;
import :math.vector;
import :math.matrix;
import :math.geometry;
import :math.barycentric;
import :structure.fragment;
import :primitive.topology;
import :structure.vertex_out;
import :pipeline.interpolator.barycentric;
import :pipeline.rasterization.rasterizer.bbox;

// ============================================================================
// Implementations
// ============================================================================

std::vector<Fragment> BoundingBoxRasterizer::rasterize(
    const Point &primitive,
    unsigned screenWidth,
    unsigned screenHeight) const
{
    throw std::invalid_argument("Bounding box rasterizer doesn't support points.");
}

std::vector<Fragment> BoundingBoxRasterizer::rasterize(
    const Line &primitive,
    unsigned screenWidth,
    unsigned screenHeight) const
{
    throw std::invalid_argument("Wireframe rasterizer doesn't support line.");
}

std::vector<Fragment> BoundingBoxRasterizer::
    rasterize(
        const Triangle &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const
{
    std::vector<Fragment> fragments;

    VertexOut a = primitive.getVertexOne();
    VertexOut b = primitive.getVertexTwo();
    VertexOut c = primitive.getVertexThree();

    BoundingBox bbox = BoundingBox(
        a.screenPosition, b.screenPosition, c.screenPosition);

    int minX = std::max(0, static_cast<int>(bbox.minX));
    int maxX = std::min(static_cast<int>(screenWidth - 1), static_cast<int>(bbox.maxX));
    int minY = std::max(0, static_cast<int>(bbox.minY));
    int maxY = std::min(static_cast<int>(screenHeight - 1), static_cast<int>(bbox.maxY));

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            // Barycentric coordinates obtention.
            BarycentricCoordinate barycentricCoordinates =
                BarycentricCoordinate::from(
                    a.screenPosition, b.screenPosition,
                    c.screenPosition, Vector2D(x, y));

            // If the point is not inside the triangle, it is discarded.
            if (barycentricCoordinates.isInsideTriangle())
            {
                // If the point isn't valid in the drawing pattern, it's discarded.
                if (drawingPattern != nullptr && !drawingPattern->isValid(barycentricCoordinates))
                    continue;

                Fragment fragment;

                BarycentricInterpolator interpolator;

                fragment.xScreen = x;
                fragment.yScreen = y;
                fragment.depth = interpolator.interpolate(
                    a.screenPosition.z(), b.screenPosition.z(),
                    c.screenPosition.z(), barycentricCoordinates);

                fragment.barycentricCoordinates = barycentricCoordinates;

                fragment.worldPosition = interpolator.interpolate(
                    a.worldPosition, b.worldPosition,
                    c.worldPosition, barycentricCoordinates);

                fragment.normal = interpolator.interpolate(
                    a.worldNormal, b.worldNormal,
                    c.worldNormal, barycentricCoordinates);
                /*

            fragment.uv =
                alpha * primitive.v0.uv +
                beta * primitive.v1.uv +
                gamma * primitive.v2.uv;

            fragment.colour =
                alpha * primitive.v0.colour +
                beta * primitive.v1.colour +
                gamma * primitive.v2.colour;
            */
                fragments.push_back(fragment);
            }
        }
    }

    if (this->normalRasterizer != nullptr)
        normalRasterizer->rasterizeNormals(primitive, fragments);

    return fragments;
}

// ============================================================================
// EOF
// ============================================================================