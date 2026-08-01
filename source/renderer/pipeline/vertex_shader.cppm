module;

#include <vector>

export module vertex_shader;

// ============================================================================
// Imports
// ============================================================================

import vector;
import transform;
import vertex_in;
import vertex_out;

// ============================================================================
// Declarations and Implementations
// ============================================================================

std::vector<VertexOut> processVertices(const RenderingInputData &inputData)
{
    int numberOfVertices = inputData.vertices.size();

    std::vector<VertexOut> processedVertices(numberOfVertices);

    MVPTransform mvpTransform = MVPTransform(
        inputData.modelTransform,
        inputData.viewTransform,
        inputData.projectionTransform);

    // #pragma omp parallel for
    for (unsigned i = 0; i < numberOfVertices; ++i)
    {

        VertexOut vertexOut{};
        out.worldPosition = inputData.modelTransform.apply(
            inputData.vertices[i].localPosition);
        out.clipPosition = inputData.mvpTransform.apply(
            inputData.vertices[i].localPosition);

        processedVertices[i] = vertexOut;
    }

    return processedVertices;
}

// ============================================================================
// EOF
// ============================================================================