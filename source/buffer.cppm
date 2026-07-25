module;

#include <string>

export module buffer;

import colour;
import tgaimage;

export class FrameBuffer
{
    TGAImage colourBuffer;
    TGAImage depthBuffer;

public:
    FrameBuffer(unsigned height, unsigned width) : colourBuffer(width, height, TGAImage::RGB), depthBuffer(width, height, TGAImage::GRAYSCALE) {}
    void setColour(unsigned x, unsigned y, const Colour &colour) { this->colourBuffer.set(x, y, colour); }
    void setDepth(unsigned x, unsigned y, double depth) { this->depthBuffer.set(x, y, TGAColour{{static_cast<unsigned char>(depth)}}); }
    bool isCurrentDepthLower(unsigned x, unsigned y, double newDepth) const { return static_cast<unsigned char>(newDepth) <= this->depthBuffer.get(x, y)[0]; }
    void renderColourBuffer(const std::string path) const { this->colourBuffer.write_tga_file(path); }
    void renderDepthBuffer(const std::string path) const { this->depthBuffer.write_tga_file(path); }
};