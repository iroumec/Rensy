module;

#include <tuple>
#include <cmath>
#include <limits>
#include <string>
#include <vector>
#include <cassert>

export module buffer;

import colour;
import tgaimage;

class DepthBuffer
{
    std::vector<double> buffer;

public:
    // The buffer is initialized with the biggest value.
    DepthBuffer(std::size_t length) : buffer(length, -std::numeric_limits<double>::infinity()) {}
    void setDepth(std::size_t index, double depth) { this->buffer[index] = depth; }
    double getDepth(std::size_t index) const { return this->buffer[index]; }
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
};

export class FrameBuffer
{
    const unsigned width;
    const unsigned height;
    TGAImage colourBuffer;
    DepthBuffer depthBuffer;

public:
    FrameBuffer(unsigned width, unsigned height)
        : width{width},
          height{height},
          colourBuffer(width, height, TGAImage::RGB),
          depthBuffer{width * height} {}

    void setColour(unsigned x, unsigned y, const Colour &colour)
    {
        this->colourBuffer.set(x, y, colour);
    }

    const Colour getColour(unsigned x, unsigned y) const
    {
        TGAColour tgaColour = this->colourBuffer.get(x, y);

        return {tgaColour[2], tgaColour[1], tgaColour[0], tgaColour[3]};
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

    std::tuple<double, double> getMinMaxDepth() const
    {
        return this->depthBuffer.getMinMaxElements();
    }

    bool isStoredDepthLower(unsigned x, unsigned y, double newDepth) const
    {
        if (x >= width || y >= height) // Overflow control.
            return false;

        std::size_t index = y * width + x;
        assert(index < width * height);

        return newDepth < this->depthBuffer.getDepth(index); // The higher the values, the more close they are to the screen.
    }

    void renderColourBuffer(const std::string path) const
    {
        this->colourBuffer.write_tga_file(path);
    }

    void renderDepthBuffer(const std::string path) const
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

    constexpr unsigned getWidth() const { return this->width; }

    constexpr unsigned getHeight() const { return this->height; }
};