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
    unsigned screenWidth;
    unsigned screenHeight;

    VBO vbo;
    EBO ebo;

    ModelTransform modelTransform;
    ViewTransform viewTransform;
    ProjectionTransform projectionTransform;

    ColourGenerator &colourGenerator;

    Colour backgroundColour;
};

// ----------------------------------------------------------------------------
// Rendereing Output Data
// ----------------------------------------------------------------------------

export struct RenderingOutputData
{
    FrameBuffer framebuffer;
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
