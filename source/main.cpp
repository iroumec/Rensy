// ============================================================================
// Includes
// ============================================================================

#include <iostream>
#include <string>

// ============================================================================
// Imports
// ============================================================================

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

    RenderingInputData inputData{
        LOG_LEVEL,
        WIDTH,
        HEIGHT,
        argv[1],
        MODEL_LOADER,
        NORMAL_CALCULATOR,
        MODEL_TRANSFORM,
        VIEW_TRANSFORM,
        PROJECTION_TRANSFORM,
        COLOUR_GENERATOR,
        LIGHTING_MODEL,
        PRIMITIVE_GENERATOR,
        RASTERIZER,
        COLOUR_CALCULATOR,
        BACKGROUND_COLOUR,
        FILTER,
    };

    RenderingOutputData output = Renderer::render(inputData);

    output.frameBuffer.renderIntoImage(outputFrameFileName);
    output.depthBuffer.renderIntoImage(outputZBufferFileName);
    return 0;
}

// ============================================================================
// EOF
// ============================================================================
