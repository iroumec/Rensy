module;

export module renderer;

// ============================================================================
// Exports-Import
// ============================================================================

export import :pipeline.depth_test;
export import :pipeline.framebuffer;
export import :transform.view;
export import :transform.model;
export import :transform.projection;

// ============================================================================
// Imports
// ============================================================================

import :structure.vbo;
import :structure.ebo;
import colour_generator;

// ============================================================================
// Declarations
// ============================================================================

// ----------------------------------------------------------------------------
// Rendereing Input Data
// ----------------------------------------------------------------------------

export struct RenderingInputData
{
    unsigned width;
    unsigned height;

    VBO vbo;
    EBO ebo;

    ModelTransform modelTransform;
    ViewTransform viewTransform;
    ProjectionTransform projectionTransform;

    ColourGenerator &colourGenerator;
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
    RenderingOutputData render(const RenderingInputData &inputData) const;
};

// ============================================================================
// EOF
// ============================================================================
