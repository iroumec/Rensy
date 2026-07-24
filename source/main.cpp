#include <iostream>
#include <string>

import model;
import drawer;
import tgaimage;
import geometry;

constexpr TGAColour white = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColour green = {0, 255, 0, 255};
constexpr TGAColour red = {0, 0, 255, 255};
constexpr TGAColour blue = {255, 128, 64, 255};
constexpr TGAColour yellow = {0, 200, 255, 255};

constexpr unsigned width = 800;
constexpr unsigned height = 800;
constexpr std::string outputFileName = "framebuffer.tga";

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
    Drawer drawer{height, width};

    drawer.drawModel(model, red, white);

    drawer.renderTGAImage(outputFileName);
    return 0;
}
