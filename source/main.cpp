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

constexpr unsigned width = 64;
constexpr unsigned height = 64;
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

    // Points.
    vec2 a{7, 3};
    vec2 b{12, 37};
    vec2 c{62, 53};

    // Lines between the points.
    drawer.drawLine(a, b, red);
    drawer.drawLine(a, c, green);
    drawer.drawLine(c, b, blue);

    // We set a colour to the points previously defined.
    // It's important that this is made after the lines.
    // In other case, the points colour will be overlaped by the line colour.
    drawer.drawPoint(a, white);
    drawer.drawPoint(b, white);
    drawer.drawPoint(c, white);

    drawer.renderTGAImage(outputFileName);
    return 0;
}
