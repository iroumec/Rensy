module;

#include <vector>

export module renderer:pipeline.shader.vertex;

// ============================================================================
// Imports
// ============================================================================

import :transform.mvp;
import :transform.view;
import :logging.logger;
import :transform.model;
import :colour.generator;
import :lighting.model.base;
import :structure.vertex_in;
import :structure.vertex_out;

// ============================================================================
// Declarations
// ============================================================================

// Clip position and projection transform is postponed to geometry shader.
export class VertexShader
{
    const ModelTransform &modelTransform;
    const ViewTransform &viewTransform;
    const ColourGenerator &colourGenerator;
    const Logger &logger;
    const LightingModel *lightingModel;

public:
    VertexShader(
        const ModelTransform &modelTransform,
        const ViewTransform &viewTransform,
        const ColourGenerator &colourGenerator,
        const Logger &logger,
        const LightingModel *lightingModel = nullptr)
        : modelTransform{modelTransform}, viewTransform{viewTransform},
          colourGenerator{colourGenerator}, logger{logger},
          lightingModel{lightingModel} {}

    std::vector<VertexOut> processVertices(
        const std::vector<VertexIn> &vertices);
};

// ============================================================================
// EOF
// ============================================================================
