module;

export module renderer;

// ============================================================================
// Exports-Import
// ============================================================================

export import :colour;
export import :transform;
export import :pipeline;
export import :structure;

// ============================================================================
// Imports
// ============================================================================

import :structure.vbo;
import :structure.ebo;
import colour;
import colour_generator;

// ============================================================================
// Declarations
// ============================================================================

// ----------------------------------------------------------------------------
// Rendereing Input Data
// ----------------------------------------------------------------------------

export struct RenderingInputData
{
    const unsigned screenWidth;
    const unsigned screenHeight;

    const VBO vbo;
    const EBO ebo;

    const ModelTransform modelTransform;
    const ViewTransform viewTransform;
    const ProjectionTransform projectionTransform;

    const Rasterizer &rasterizer;

    const ColourCalculator &colourCalculator;
    const ColourIntensifierFactory *colourIntensifierFactory;

    const Colour backgroundColour;
};

// ----------------------------------------------------------------------------
// Rendereing Output Data
// ----------------------------------------------------------------------------

export struct RenderingOutputData
{
    FrameBuffer frameBuffer;
    DepthBuffer depthBuffer;
};

// ----------------------------------------------------------------------------
// Renderer
// ----------------------------------------------------------------------------

export class Renderer
{
public:
    static RenderingOutputData render(const RenderingInputData &inputData);
};

// ============================================================================
// EOF
// ============================================================================
