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
        vertexOut.viewPosition = viewTransform.apply(vertexOut.worldPosition);
        vertexOut.clipPosition = mvpTransform.apply(vertices[i].localPosition);

        vertexOut.colour.set(colourGenerator());

        Vector4D normal = vertices[i].normal;
        normal.w() = 0;                                       // Directions are treated differently than points. They don't have its w value in 1, but 0.
        vertexOut.worldNormal = modelTransform.apply(normal); // Normals only available in local, world and camera.
        vertexOut.viewNormal = viewTransform.apply(vertexOut.worldNormal);

        processedVertices[i] = vertexOut;
    }

    return processedVertices;
}

// ============================================================================
// EOF
// ============================================================================