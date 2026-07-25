#include <iostream>
#include <string>

import model;
import drawer;
import tgaimage;
import geometry;
// import configuration;

constexpr unsigned width = 800;
constexpr unsigned height = 800;
constexpr std::string outputFileName = "framebuffer.tga";

// BGRA.
[[maybe_unused]] constexpr TGAColour white{{255, 255, 255, 255}};
[[maybe_unused]] constexpr TGAColour green{{0, 255, 0, 255}};
[[maybe_unused]] constexpr TGAColour red{{0, 0, 255, 255}};
[[maybe_unused]] constexpr TGAColour blue{{255, 0, 0, 255}};
[[maybe_unused]] constexpr TGAColour yellow{{0, 255, 255, 255}};
[[maybe_unused]] constexpr TGAColour cyan{{255, 255, 0, 255}};
[[maybe_unused]] constexpr TGAColour magenta{{255, 0, 255, 255}};
[[maybe_unused]] constexpr TGAColour orange{{0, 165, 255, 255}};
[[maybe_unused]] constexpr TGAColour purple{{128, 0, 128, 255}};

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
