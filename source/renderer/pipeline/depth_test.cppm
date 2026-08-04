module;

#include <tuple>
#include <cmath>
#include <limits>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>

export module renderer:pipeline.depth_test;

// ============================================================================
// Imports
// ============================================================================

import :output.image.tga;
import :structure.fragment;

// ============================================================================
// Declarations and Implementations
// ============================================================================

class DepthBuffer
{
    const unsigned width;
    const unsigned height;
    std::vector<double> buffer;

public:
    // The buffer is initialized with the biggest value.
    DepthBuffer(unsigned width, unsigned height)
        : width{width}, height{height},
          buffer(width * height, -std::numeric_limits<double>::infinity()) {}

    void setDepth(unsigned int x, unsigned int y, double depth)
    {
        assert(x >= 0 && x < this->width);
        assert(y >= 0 && y < this->height);

        std::size_t index = y * width + x;
        assert(index < width * height);

        this->buffer[index] = depth;
    }
    double getDepth(unsigned int x, unsigned int y) const
    {
        assert(x >= 0 && x < this->width);
        assert(y >= 0 && y < this->height);

        std::size_t index = y * width + x;
        return this->buffer[index];
    }

    constexpr std::vector<Fragment> process(
        const std::vector<Fragment> &fragments)
    {
        std::vector<Fragment> processedFragments;

        for (Fragment fragment : fragments)
            if (this->testAndSet(fragment.xScreen, fragment.yScreen, fragment.depth))
                processedFragments.push_back(fragment);

        return processedFragments;
    }

    bool testAndSet(unsigned x, unsigned y, double depth)
    {
        assert(x >= 0 && x < this->width);
        assert(y >= 0 && y < this->height);

        // >= to keep always the last vertex analized.
        if (depth >= this->getDepth(x, y)) // The higher the values, the more close they are to the screen.)
        {
            this->setDepth(x, y, depth);
            return true;
        }

        return false;
    }

    std::tuple<double, double> getMinMaxDepth() const
    {
        double min = std::numeric_limits<double>::infinity();
        double max = -std::numeric_limits<double>::infinity();

        for (double depth : buffer)
        {
            if (!std::isfinite(depth))
                continue;

            if (depth < min)
                min = depth;

            if (depth > max)
                max = depth;
        }

        return {min, max};
    }

    void renderIntoImage(const std::string path) const
    {
        TGAImage imageBuffer(this->width, this->height, TGAImage::GRAYSCALE);

        auto [minDepth, maxDepth] = this->getMinMaxDepth();

        minDepth -= 0.5; // So the things too distant aren't completely black.

        for (unsigned row = 0; row < this->height; row++)
            for (unsigned column = 0; column < this->width; column++)
                imageBuffer.set(
                    column,
                    row,
                    TGAColour{{static_cast<unsigned char>(
                        (this->getDepth(column, row) - minDepth) / (maxDepth - minDepth) * 255)}});

        imageBuffer.write_tga_file(path);
    }

    constexpr unsigned getWidth() const
    {
        return this->width;
    }

    constexpr unsigned getHeight() const
    {
        return this->height;
    }
};

// ============================================================================
// EOF
// ============================================================================