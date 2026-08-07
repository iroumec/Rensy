module;

#include <vector>

export module renderer:pipeline.shader.vertex;

// ============================================================================
// Imports
// ============================================================================

import :transform.mvp;
import :transform.view;
import :transform.model;
import :colour.generator;
import :lighting.model.base;
import :structure.vertex_in;
import :structure.vertex_out;
import :transform.projection;

// ============================================================================
// Declarations
// ============================================================================

export class VertexShader
{
    const ModelTransform &modelTransform;
    const ViewTransform &viewTransform;
    const ProjectionTransform &projectionTransform;
    const ColourGenerator &colourGenerator;
    const LightingModel *lightingModel;

public:
    VertexShader(
        const ModelTransform &modelTransform,
        const ViewTransform &viewTransform,
        const ProjectionTransform &projectionTransform,
        const ColourGenerator &colourGenerator,
        const LightingModel *lightingModel = nullptr)
        : modelTransform{modelTransform}, viewTransform{viewTransform},
          projectionTransform{projectionTransform},
          colourGenerator{colourGenerator}, lightingModel{lightingModel} {}

    std::vector<VertexOut> processVertices(
        const std::vector<VertexIn> &vertices);
};

// ============================================================================
// EOF
// ============================================================================
