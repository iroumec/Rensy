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
import :interpolation.data;
import :primitive.topology;
import :structure.vertex_out;
import :structure.prefragment;
import :rasterization.algorithm.bbox;

// ============================================================================
// Implementations
// ============================================================================

std::vector<PreFragment> BoundingBoxAlgorithm::
    rasterize(
        const Triangle &primitive,
        unsigned screenWidth,
        unsigned screenHeight) const
{
    std::vector<PreFragment> prefragments;

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

                InterpolationData interpolationData;
                interpolationData.influences.push_back({a, barycentricCoordinates.alpha});
                interpolationData.influences.push_back({b, barycentricCoordinates.beta});
                interpolationData.influences.push_back({c, barycentricCoordinates.gamma});

                PreFragment prefragment(x, y, interpolationData);

                prefragments.push_back(prefragment);
            }
        }
    }

    return prefragments;
}

// ============================================================================
// EOF
// ============================================================================