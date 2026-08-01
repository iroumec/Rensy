module;

#include <tuple>
#include <cmath>
#include <limits>
#include <algorithm>

export module renderer:filter;

import colour;
import :pipeline.depth_test;
import :pipeline.framebuffer;

export class Filter
{

public:
    virtual constexpr void apply(FrameBuffer &buffer, const DepthBuffer &depthBuffer) const = 0;
};

// The deeper the pixel, the more fog it gets.
export class FogFilter : public Filter
{
    const Colour fogColour;
    const double minFogIntensity;
    const double maxFogIntensity;

public:
    FogFilter(const Colour &colour, double minIntensity = 0.1, double maxIntensity = 0.9)
        : fogColour(colour), minFogIntensity(minIntensity), maxFogIntensity(maxIntensity) {}

    constexpr void apply(FrameBuffer &buffer, const DepthBuffer &depthBuffer) const override
    {
        auto [minDepth, maxDepth] = depthBuffer.getMinMaxDepth();
        if (minDepth == maxDepth)
            return;

        for (unsigned x = 0; x < buffer.getWidth(); x++)
            for (unsigned y = 0; y < buffer.getHeight(); y++)
            {
                double depth = depthBuffer.getDepth(x, y);

                if (!std::isfinite(depth))
                    continue;

                double intensity = (depth - minDepth) / (maxDepth - minDepth);
                buffer.setColour(x, y, buffer.getColour(x, y).blend(this->fogColour, std::clamp(1. - intensity, minFogIntensity, maxFogIntensity)));
            }
    }
};

// The nearest the pixel, the more bright it gets.
export class BrightFilter : public Filter
{
    const Colour brightColour;
    const double minBrightIntensity;
    const double maxBrightIntensity;

public:
    BrightFilter(const Colour &colour, double minIntensity = 0., double maxIntensity = 0.5)
        : brightColour(colour), minBrightIntensity(minIntensity), maxBrightIntensity(maxIntensity) {}

    constexpr void apply(FrameBuffer &buffer, const DepthBuffer &depthBuffer) const override
    {
        auto [minDepth, maxDepth] = depthBuffer.getMinMaxDepth();
        if (minDepth == maxDepth)
            return;

        for (unsigned x = 0; x < buffer.getWidth(); x++)
            for (unsigned y = 0; y < buffer.getHeight(); y++)
            {
                double depth = depthBuffer.getDepth(x, y);

                if (!std::isfinite(depth))
                    continue;

                double intensity = (depth - minDepth) / (maxDepth - minDepth);
                buffer.setColour(x, y, buffer.getColour(x, y).blend(this->brightColour, std::clamp(intensity, minBrightIntensity, maxBrightIntensity)));
            }
    }
};