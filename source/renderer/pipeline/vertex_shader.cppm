module;

#include <vector>

export module renderer:pipeline.vertex_shader;

// ============================================================================
// Imports
// ============================================================================

import :transform.mvp;
import :transform.view;
import :transform.model;
import :structure.vertex_in;
import :structure.vertex_out;
import :transform.projection;
import colour_generator;

// ============================================================================
// Declarations and Implementations
// ============================================================================

std::vector<VertexOut> processVertices(
    const std::vector<VertexIn> &vertices,
    const ModelTransform &modelTransform,
    const ViewTransform &viewTransform,
    const ProjectionTransform &projectionTransform,
    const ColourGenerator &colourGenerator)
{
    int numberOfVertices = vertices.size();

    std::vector<VertexOut> processedVertices(numberOfVertices);

    MVPTransform mvpTransform = MVPTransform(
        modelTransform,
        viewTransform,
        projectionTransform);

    // #pragma omp parallel for
    for (unsigned i = 0; i < numberOfVertices; ++i)
    {
        VertexOut vertexOut{};
        vertexOut.worldPosition = modelTransform.apply(vertices[i].localPosition);
        vertexOut.clipPosition = mvpTransform.apply(vertices[i].localPosition);
        vertexOut.colour = colourGenerator();

        processedVertices[i] = vertexOut;
    }

    return processedVertices;
}

// ============================================================================
// EOF
// ============================================================================