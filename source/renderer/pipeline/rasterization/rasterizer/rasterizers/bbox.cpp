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
import :structure.triangle;
import :structure.fragment;
import :pipeline.rasterization.rasterizer.bbox;

// ============================================================================
// Implementations
// ============================================================================

std::vector<Fragment> BoundingBoxRasterizer::
    rasterize(
        const Triangle &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const
{
    std::vector<Fragment> fragments;

    Vector3D a = primitive.v0.screenPosition;
    Vector3D b = primitive.v1.screenPosition;
    Vector3D c = primitive.v2.screenPosition;

    BoundingBox bbox = BoundingBox(a, b, c);

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
                BarycentricCoordinate::from(a, b, c, Vector2D(x, y));

            // If the point is not inside the triangle, it is discarded.
            if (barycentricCoordinates.isInsideTriangle())
            {
                // If the point isn't valid in the drawing pattern, it's discarded.
                if (drawingPattern != nullptr && !drawingPattern->isValid(barycentricCoordinates))
                    continue;

                Fragment fragment;

                fragment.xScreen = x;
                fragment.yScreen = y;
                fragment.depth = barycentricCoordinates.alpha * a.z() +
                                 barycentricCoordinates.beta * b.z() +
                                 barycentricCoordinates.gamma * c.z();

                fragment.barycentricCoordinates = barycentricCoordinates;

                fragment.worldPosition =
                    barycentricCoordinates.alpha * primitive.v0.worldPosition +
                    barycentricCoordinates.beta * primitive.v1.worldPosition +
                    barycentricCoordinates.gamma * primitive.v2.worldPosition;

                fragment.normal =
                    barycentricCoordinates.alpha * primitive.v0.worldNormal +
                    barycentricCoordinates.beta * primitive.v1.worldNormal +
                    barycentricCoordinates.gamma * primitive.v2.worldNormal;
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