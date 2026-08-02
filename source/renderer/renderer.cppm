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

    const ColourGenerator &colourGenerator;

    const Rasterizer &rasterizer;

    const ColourCalculator &colourCalculator;
    const ColourShadingFactory *colourShadingFactory;

    const Colour backgroundColour;

    const Filter *filter;
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
