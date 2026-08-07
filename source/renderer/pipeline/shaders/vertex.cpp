module;

#include <vector>

module renderer;

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

std::vector<VertexOut> VertexShader::processVertices(
    const std::vector<VertexIn> &vertices)
{
    int numberOfVertices = vertices.size();

    std::vector<VertexOut> processedVertices(numberOfVertices);

    MVPTransform mvpTransform = MVPTransform(
        this->modelTransform,
        this->viewTransform,
        this->projectionTransform);

    // #pragma omp parallel for
    for (unsigned i = 0; i < numberOfVertices; ++i)
    {
        VertexOut vertexOut{};
        vertexOut.worldPosition =
            this->modelTransform.apply(vertices[i].localPosition);
        vertexOut.viewPosition =
            this->viewTransform.apply(vertexOut.worldPosition);
        vertexOut.clipPosition =
            this->mvpTransform.apply(vertices[i].localPosition);

        vertexOut.colour.set(this->colourGenerator());

        Vector4D normal = vertices[i].normal;
        normal.w() = 0;                                       // Directions are treated differently than points. They don't have its w value in 1, but 0.
        vertexOut.worldNormal = modelTransform.apply(normal); // Normals only available in local, world and camera.
        vertexOut.viewNormal = viewTransform.apply(vertexOut.worldNormal);

        if (this->lightingModel)
            this->lightingModel->processVertex(vertexOut);

        processedVertices[i] = vertexOut;
    }

    return processedVertices;
}

// ============================================================================
// EOF
// ============================================================================