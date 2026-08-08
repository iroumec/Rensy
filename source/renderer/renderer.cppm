module;

#include <string>

export module renderer;

// ============================================================================
// Exports-Imports
// ============================================================================

export import :math;
export import :model;
export import :normal;
export import :colour;
export import :logging;
export import :pipeline;
export import :lighting;
export import :primitive;
export import :transform;
export import :structure;
export import :interpolation;
export import :drawing_pattern; // TODO: Change this.

// ============================================================================
// Declarations
// ============================================================================

// ----------------------------------------------------------------------------
// Rendereing Input Data
// ----------------------------------------------------------------------------

export struct RenderingInputData
{
    const LogLevel logLevel;

    const unsigned screenWidth;
    const unsigned screenHeight;

    const std::string &fileName;

    const ModelLoader &modelLoader;
    const NormalCalculator &normalCalculator;

    const ModelTransform modelTransform;
    const ViewTransform viewTransform;
    const ProjectionTransform projectionTransform;

    const ColourGenerator &colourGenerator;

    const LightingModel *lightingModel;

    const PrimitiveGenerator *primitiveGenerator;

    const Rasterizer &rasterizer;

    const ColourCalculator &colourCalculator;

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
