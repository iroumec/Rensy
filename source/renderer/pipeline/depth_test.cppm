module;

#include <tuple>
#include <cmath>
#include <limits>
#include <string>
#include <vector>
#include <cassert>

export module renderer:pipeline.depth_test;

// ============================================================================
// Imports
// ============================================================================

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
    DepthBuffer(std::size_t length) : buffer(length, -std::numeric_limits<double>::infinity()) {}
    void setDepth(std::size_t index, double depth) { this->buffer[index] = depth; }
    double getDepth(std::size_t index) const { return this->buffer[index]; }

    export constexpr std::vector<Fragment> applyViewportTransform(
        const std::vector<Fragment> &fragments)
    {
        std::vector<Fragment> processedFragments;

        for (fragment : fragments)
            if (depthTest.testAndSet(fragment))
                processedFragments.push_back(fragment);
    }

    bool testAndSet(unsigned x, unsigned y, double depth)
    {
        if (this->isStoredDepthLower(x, y, depth))
        {
            this->setDepth(x, y, depth);
            return true;
        }

        return false;
    }

    void setDepth(unsigned x, unsigned y, double depth)
    {
        assert(x >= 0 && x < this->width);
        assert(y >= 0 && y < this->height);

        std::size_t index = y * width + x;

        this->depthBuffer.setDepth(index, depth);
    }

    double getDepth(unsigned x, unsigned y) const
    {
        std::size_t index = y * width + x;
        assert(index < width * height);

        return this->depthBuffer.getDepth(index);
    }

    std::tuple<double, double> getMinMaxElements() const
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

    bool isStoredDepthLower(unsigned x, unsigned y, double newDepth) const
    {
        if (x >= width || y >= height) // Overflow control.
            return false;

        std::size_t index = y * width + x;
        assert(index < width * height);

        return newDepth < this->depthBuffer.getDepth(index); // The higher the values, the more close they are to the screen.
    }

    void renderIntoImage(const std::string path) const
    {
        TGAImage imageBuffer(this->width, this->height, TGAImage::GRAYSCALE);

        auto [minDepth, maxDepth] = this->depthBuffer.getMinMaxElements();

        minDepth -= 0.5; // So the things too distant aren't completely black.

        for (unsigned row = 0; row < this->height; row++)
            for (unsigned column = 0; column < this->width; column++)
                imageBuffer.set(
                    column,
                    row,
                    TGAColour{{static_cast<unsigned char>(
                        (this->depthBuffer.getDepth(row * this->width + column) - minDepth) / (maxDepth - minDepth) * 255)}});

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