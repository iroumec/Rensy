module;

#include <tuple>
#include <cmath>
#include <limits>
#include <algorithm>

export module renderer:colour.filter.bright;

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

// The nearest the pixel, the more bright it gets.
export class BrightFilter : public Filter
{
    const Colour brightColour;
    const double minBrightIntensity;
    const double maxBrightIntensity;

public:
    BrightFilter(
        const Colour &colour,
        double minIntensity = 0.,
        double maxIntensity = 0.5)
        : brightColour(colour),
          minBrightIntensity(minIntensity),
          maxBrightIntensity(maxIntensity) {}

    constexpr void apply(
        FrameBuffer &colourBuffer,
        const DepthBuffer &depthBuffer) const override
    {
        auto [minDepth, maxDepth] = depthBuffer.getMinMaxDepth();
        if (minDepth == maxDepth)
            return;

        for (unsigned x = 0; x < colourBuffer.getWidth(); x++)
            for (unsigned y = 0; y < colourBuffer.getHeight(); y++)
            {
                double depth = depthBuffer.getDepth(x, y);

                if (!std::isfinite(depth))
                    continue;

                double intensity = (depth - minDepth) / (maxDepth - minDepth);
                colourBuffer.setColour(
                    x, y,
                    colourBuffer.getColour(x, y).blend(
                        this->brightColour,
                        std::clamp(
                            intensity,
                            minBrightIntensity,
                            maxBrightIntensity)));
            }
    }
};

// ============================================================================
// EOF
// ============================================================================