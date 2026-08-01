module;

export module renderer;

// ============================================================================
// Exports-Import
// ============================================================================

export import :depth_test;
export import :framebuffer;
export import :transform.view;
export import :transform.model;
export import :transform.projection;

// ============================================================================
// Imports
// ============================================================================

import :vbo;
import :ebo;
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

    ColourGenerator colourGenerator;
};

// ----------------------------------------------------------------------------
// Rendereing Output Data
// ----------------------------------------------------------------------------

export struct RenderingOutputData
{
    Framebuffer framebuffer;
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
