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
import :structure.vertex_in;
import :structure.vertex_out;
import :transform.projection;

// ============================================================================
// Declarations
// ============================================================================

export class VertexShader
{
    const LightingModel *lightingModel;
    const ColourGenerator &colourGenerator;

public:
    FragmentShader(
        const ColourGenerator &colourGenerator,
        const LightingModel *lightingModel = nullptr)
        : colourGenerator{colourGenerator}, lightingModel{lightingModel} {}

    std::vector<VertexOut> processVertices(
        const std::vector<VertexIn> &vertices,
        const ModelTransform &modelTransform,
        const ViewTransform &viewTransform,
        const ProjectionTransform &projectionTransform);

    // ============================================================================
    // EOF
    // ============================================================================
