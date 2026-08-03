module;

#include <tuple>
#include <cmath>
#include <limits>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>

export module renderer:pipeline.framebuffer;

// ============================================================================
// Imports
// ============================================================================

import :structure.colour;
import :output.image.tga;
import :structure.fragment;

// ============================================================================
// Declarations
// ============================================================================

export class FrameBuffer
{
    const unsigned width;
    const unsigned height;
    TGAImage colourBuffer;

public:
    FrameBuffer(unsigned width, unsigned height, const Colour &backgroundColour = black)
        : width{width},
          height{height},
          colourBuffer(width, height, TGAImage::RGB)
    {
        for (unsigned x = 0; x < this->width; ++x)
            for (unsigned y = 0; y < this->height; ++y)
                this->colourBuffer.set(x, y, backgroundColour);
    }

    constexpr void process(const std::vector<Fragment> &fragments)
    {
        for (Fragment fragment : fragments)
            this->setColour(
                fragment.xScreen,
                fragment.yScreen,
                fragment.colour.get());
    }

    void setColour(unsigned x, unsigned y, const Colour &colour)
    {
        this->colourBuffer.set(x, y, colour);
    }

    const Colour getColour(unsigned x, unsigned y) const
    {
        TGAColour tgaColour = this->colourBuffer.get(x, y);

        return {tgaColour[2], tgaColour[1], tgaColour[0], tgaColour[3]};
    }

    void renderIntoImage(const std::string path) const
    {
        this->colourBuffer.write_tga_file(path);
    }

    constexpr unsigned getWidth() const { return this->width; }

    constexpr unsigned getHeight() const { return this->height; }
};

// ============================================================================
// EOF
// ============================================================================
