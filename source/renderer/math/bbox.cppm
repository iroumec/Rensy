module;

#include <cmath>

export module renderer:math.bbox;

import :math.vector.vector_2d;

export class BoundingBox
{
public:
    const double minX;
    const double minY;
    const double maxX;
    const double maxY;

    BoundingBox(Vector2D a, Vector2D b, Vector2D c)
        : minX{std::min(std::min(a.x(), b.x()), c.x())},
          minY{std::min(std::min(a.y(), b.y()), c.y())},
          maxX{std::max(std::max(a.x(), b.x()), c.x())},
          maxY{std::max(std::max(a.y(), b.y()), c.y())} {}
};