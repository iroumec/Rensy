// ============================================================================
// Includes
// ============================================================================

#include <iostream>
#include <string>

// ============================================================================
// Imports
// ============================================================================

import model;
import colour;
import tgaimage;
import renderer;
import configuration;

// ============================================================================
// Functions
// ============================================================================

int main(int argc, char **argv)
{
    // Number of arguments check.
    if (argc < 2)
    {
        std::cerr << "A model must be passed as an argument." << std::endl;
        // std::cerr << "Usage: " << argv[0] << " obj/model.obj" << std::endl;
        return 1;
    }

    initializeConfiguration();

    Model model{argv[1]};

    RenderingInputData{

    };

    RASTERIZER.draw(model, buffer, COLOUR_GENERATOR, getMVPTransform());

    if (FILTER != nullptr)
        FILTER->apply(buffer);

    buffer.renderColourBuffer(outputFrameFileName);
    buffer.renderDepthBuffer(outputZBufferFileName);
    return 0;
}

// ============================================================================
// EOF
// ============================================================================
