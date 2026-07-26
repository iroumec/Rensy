module;

#include <string>

export module buffer;

import colour;
import tgaimage;

export class FrameBuffer
{
    const unsigned width;
    const unsigned height;
    TGAImage colourBuffer;
    TGAImage depthBuffer;

public:
    FrameBuffer(unsigned width, unsigned height)
        : width{width},
          height{height},
          colourBuffer(width, height, TGAImage::RGB),
          depthBuffer(width, height, TGAImage::GRAYSCALE) {}

    void setColour(unsigned x, unsigned y, const Colour &colour)
    {
        this->colourBuffer.set(x, y, colour);
    }

    void setDepth(unsigned x, unsigned y, unsigned char depth)
    {
        this->depthBuffer.set(x, y, TGAColour{{depth}});
    }

    bool isCurrentDepthLower(unsigned x, unsigned y, unsigned char newDepth) const
    {
        return newDepth <= this->depthBuffer.get(x, y)[0];
    }

    void renderColourBuffer(const std::string path) const
    {
        this->colourBuffer.write_tga_file(path);
    }

    void renderDepthBuffer(const std::string path) const
    {
        this->depthBuffer.write_tga_file(path);
    }

    unsigned getWidth() const { return this->width; }

    unsigned getHeight() const { return this->height; }
};