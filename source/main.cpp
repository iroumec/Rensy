#include <iostream>
#include <string>

import model;
import colour;
import buffer;
import tgaimage;
import rasterizer;
import configuration;

int main(int argc, char **argv)
{
    // Number of arguments check.
    if (argc < 2)
    {
        std::cerr << "A model must be passed as an argument." << std::endl;
        // std::cerr << "Usage: " << argv[0] << " obj/model.obj" << std::endl;
        return 1;
    }

    Model model{argv[1]};
    FrameBuffer buffer{WIDTH, HEIGHT};
    // VertexRasterizer rasterizer;
    // WireframeRasterizer rasterizer;
    // ScanlineRasterizer rasterizer;
    BoundingBoxRasterizer rasterizer{COLOUR_CALCULATOR, COLOUR_INTENSIFIER, DRAWING_PATTERN};

    rasterizer.draw(model, buffer, COLOUR_GENERATOR, ROTATION);

    buffer.renderColourBuffer(outputFrameFileName);
    buffer.renderDepthBuffer(outputZBufferFileName);
    return 0;
}
