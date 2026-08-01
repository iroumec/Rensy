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

    auto [vbo, ebo] = ObjModel::load(argv[1]);

    RenderingInputData inputData{
        WIDTH,
        HEIGHT,
        vbo,
        ebo,
        MODEL_TRANSFORM,
        VIEW_TRANSFORM,
        PROJECTION_TRANSFORM,
        COLOUR_GENERATOR,
        RASTERIZER,
        COLOUR_CALCULATOR,
        COLOUR_INTENSIFIER,
        BACKGROUND_COLOUR,
    };

    RenderingOutputData output = Renderer::render(inputData);

    output.frameBuffer.renderIntoImage(outputFrameFileName);
    output.depthBuffer.renderIntoImage(outputZBufferFileName);
    return 0;
}

// ============================================================================
// EOF
// ============================================================================
