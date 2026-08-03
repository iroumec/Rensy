module;

#include <vector>

export module renderer:normal.rasterizer.line;

// ============================================================================
// Imports
// ============================================================================

import :math.bresenham;
import :structure.triangle;
import :structure.fragment;
import :normal.rasterizer.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class LineNormalRasterizer : public NormalRasterizer
{
    const double normalDistance;
    const Colour normalColour;

public:
    LineNormalRasterizer(double normalDistance, Colour normalColour)
        : normalDistance(normalDistance), normalColour(normalColour) {}

    constexpr void rasterizeNormals(
        const Triangle &primitive,
        std::vector<Fragment> &fragments) const override
    {
        std::vector<Vector2D> vectors;

        for (const auto &vertex : primitive.vertices())
        {
            Vector3D start = vertex.worldPosition;
            Vector3D end =
                start +
                vertex.worldNormal.normalize() * normalDistance;

            drawLine(start, end, vectors);
        }

        for (const Vector2D &vector : vectors)
        {
            Fragment fragment;

            fragment.xScreen = vector.x();
            fragment.yScreen = vector.y();
            fragment.colour.set(this->normalColour);
            fragment.colour.lock();

            fragments.push_back(fragment);
        }
    }
};

// ============================================================================
// EOF
// ============================================================================