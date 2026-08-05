module;

#include <cmath>
#include <vector>

export module renderer:colour.shading.instance.depth;

// ============================================================================
// Imports
// ============================================================================

import :math.barycentric;
import :structure.fragment;
import :colour.shading.instance.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class DepthShading : public Shading
{
    const std::vector<double> depths;
    const double minDepth;
    const double maxDepth;

public:
    DepthShading(const double &depths, double minDepth, double maxDepth)
        : depths{depths}, minDepth{minDepth}, maxDepth{maxDepth} {}

    constexpr void adjustColour(Fragment &fragment) const override
    {
        double intensity = 1.0;

        if (maxDepth != minDepth)
        {
            intensity =
                (fragment.depth - minDepth) /
                (maxDepth - minDepth);
        }

        fragment.colour.set(fragment.colour.get() * intensity);
    }
};

// ============================================================================
// EOF
// ============================================================================
