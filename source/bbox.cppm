module;

#include <cmath>

export module bbox;

import geometry;

export class BoundingBox
{
public:
    const double minX;
    const double minY;
    const double maxX;
    const double maxY;

    BoundingBox(vec2 a, vec2 b, vec2 c)
        : minX{std::min(std::min(a.x, b.x), c.x)},
          minY{std::min(std::min(a.y, b.y), c.y)},
          maxX{std::max(std::max(a.x, b.x), c.x)},
          maxY{std::max(std::max(a.y, b.y), c.y)}
    {
    }
};