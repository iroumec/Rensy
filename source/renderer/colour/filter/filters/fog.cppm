module;

#include <tuple>
#include <cmath>
#include <limits>
#include <algorithm>
#include <iostream>

export module renderer:colour.filter.fog;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;
import :colour.filter.base;
import :pipeline.depth_test;
import :pipeline.framebuffer;

// ============================================================================
// Declarations and Implementations
// ============================================================================

// The deeper the pixel, the more fog it gets.
export class FogFilter : public Filter
{
    const Colour fogColour;
    const double minFogIntensity;
    const double maxFogIntensity;

public:
    FogFilter(const Colour &colour,
              double minIntensity = 0.1,
              double maxIntensity = 0.9)
        : fogColour(colour),
          minFogIntensity(minIntensity),
          maxFogIntensity(maxIntensity) {}

    constexpr void apply(
        FrameBuffer &colourBuffer,
        const DepthBuffer &depthBuffer) const override
    {
        auto [minDepth, maxDepth] = depthBuffer.getMinMaxDepth();
        if (minDepth == maxDepth)
            return;

        for (unsigned x = 0; x < colourBuffer.getWidth(); ++x)
            for (unsigned y = 0; y < colourBuffer.getHeight(); ++y)
            {
                double depth = depthBuffer.getDepth(x, y);

                if (!std::isfinite(depth))
                    continue;

                double intensity = (depth - minDepth) / (maxDepth - minDepth);
                colourBuffer.setColour(
                    x, y,
                    colourBuffer.getColour(x, y).blend(
                        this->fogColour,
                        std::clamp(
                            1. - intensity,
                            minFogIntensity,
                            maxFogIntensity)));
            }
    }
};

// ============================================================================
// EOF
// ============================================================================