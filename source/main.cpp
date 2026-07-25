#include <iostream>

import model;
import drawer;
import colours;
import tgaimage;
import geometry;
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
    Drawer drawer{height, width};

    drawer.drawModel(model, red, white);

    drawer.renderTGAImage(outputFileName);
    return 0;
}
