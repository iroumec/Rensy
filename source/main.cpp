#include <iostream>
#include <string>

import model;
import drawer;
import colour;
import tgaimage;
import geometry;
import configuration;
import model_rasterizer;
import rasterizer;

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
    ModelRasterizer<BoundingBoxRasterizer> rasterizer{height, width};
    RandomColourGenerator colourGenerator;

    rasterizer.draw(model, colourGenerator);

    rasterizer.renderFrameBufferToTGAImage(outputFrameFileName);
    rasterizer.renderZBufferToTGAImage(outputZBufferFileName);
    return 0;
}
