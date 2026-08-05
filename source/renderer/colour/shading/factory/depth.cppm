module;

#include <cmath>
#include <memory>
#include <vector>
#include <limits>

export module renderer:colour.shading.factory.depth;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology.base;
import :colour.shading.factory.base;
import :colour.shading.instance.base;
import :colour.shading.instance.depth;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class DepthShadingFactory : public ShadingFactory
{
public:
    std::shared_ptr<Shading> instance(
        const Primitive &primitive) const override
    {
        std::vector<double> depths;
        double minDepth = std::numeric_limits<float>::min();
        double maxDepth = std::numeric_limits<float>::max();

        for (const VertexOut &vertex : primitive.vertices())
        {
            depths.push_back(vertex.screenPosition);
            minDepth = std::min(vertex.screenPosition, minDepth);
            maxDepth = std::max(vertex.screenPosition, maxDepth);
        }

        return std::make_shared<DepthShading>(depths, minDepth, maxDepth);
    }
};

// ============================================================================
// EOF
// ============================================================================