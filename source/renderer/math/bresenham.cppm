module;

#include <cmath>
#include <vector>

export module renderer:math.bresenham;

// ============================================================================
// Imports
// ============================================================================

import :math.geometry;
import :math.vector.vector_2d;

// ============================================================================
// Declarations
// ============================================================================

// Bresengam's line algorithm.
export void drawLine(Vector2D a, Vector2D b, std::vector<Vector2D> &out)
{
    out.push_back(a);
    out.push_back(b);

    // Is the line more vertical than horizontal?
    bool steep = std::abs(a.x() - b.x()) < std::abs(a.y() - b.y());
    if (steep)
    { // If that's the case, the image is transposed.
        std::swap(a.x(), a.y());
        std::swap(b.x(), b.y());
    }

    // Due to x increasing in the below loop, and it starting
    // at ax, it cannot draw right-to-left lines.
    if (a.x() > b.x())
    { // Make it left-to-right.
        std::swap(a.x(), b.x());
        std::swap(a.y(), b.y());
    }

    for (unsigned x = a.x(); x <= b.x(); ++x)
    {
        unsigned y = round(interpolateY(a, b, x));

        // If the image was transposed (steep), it's de-transposed.
        if (steep)
            out.push_back(Vector2D(y, x));
        else
            out.push_back(Vector2D(x, y));
    }
}

// ============================================================================
// EOF
// ============================================================================