module;

#include <vector>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :transform.view;
import :logging.logger;
import :transform.model;
import :colour.generator;
import :structure.vertex_in;
import :structure.vertex_out;
import :transform.projection;
import :pipeline.shader.vertex;

// ============================================================================
// Implementations
// ============================================================================

std::vector<VertexOut> VertexShader::processVertices(
    const std::vector<VertexIn> &vertices)
{
    int numberOfVertices = vertices.size();

    std::vector<VertexOut> processedVertices(numberOfVertices);

    // #pragma omp parallel for
    for (unsigned i = 0; i < numberOfVertices; ++i)
    {
        VertexOut vertexOut{};
        vertexOut.worldPosition =
            this->modelTransform.apply(vertices[i].localPosition);
        vertexOut.viewPosition =
            this->viewTransform.apply(vertexOut.worldPosition);

        vertexOut.colour.set(this->colourGenerator());

        Vector4D normal = vertices[i].normal;
        normal.w() = 0;                                       // Directions are treated differently than points. They don't have its w value in 1, but 0.
        vertexOut.worldNormal = modelTransform.apply(normal); // Normals only available in local, world and camera.
        vertexOut.viewNormal = viewTransform.apply(vertexOut.worldNormal);

        if (this->lightingModel)
            this->lightingModel->processVertex(vertexOut);

        this->logger.traceEvery<100>(
            "Vertex {} -> World position: {}, view position {}",
            i, vertexOut.worldPosition.toString(),
            vertexOut.viewPosition.toString());

        processedVertices[i] = vertexOut;
    }

    return processedVertices;
}

// ============================================================================
// EOF
// ============================================================================