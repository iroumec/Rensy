module;

#include <vector>
#include <memory>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :logging.logger;
import :structure.vertex_out;
import :primitive.topology.base;
import :pipeline.primitive_assembly;
import :primitive.topology.triangle;

// ============================================================================
// Declarations
// ============================================================================

std::vector<std::unique_ptr<Primitive>> PrimitiveAssembler::assemblyPrimitives(
    const std::vector<VertexOut> &vertices,
    const std::vector<int> &faces) const // TODO: vector de unsigned.
{
    if (faces.size() % 3 != 0)
        throw std::invalid_argument("Face index count must be a multiple of 3.");

    const std::size_t numberOfFaces = faces.size() / 3;

    std::vector<std::unique_ptr<Primitive>> primitives(numberOfFaces);

    // #pragma omp parallel for
    for (std::size_t i = 0; i < numberOfFaces; ++i)
    {
        // Each face is stored as three consecutive indices into the vertices array.
        // faceNumber * 3 gives the first index of the face, and vertexNumber (0-2)
        // selects one of its three vertices.

        // If faceNumber = 0, we are placed in the first face. Increasing vertexNumber
        // in [0, 2] gives us the vertex.
        const std::size_t index = i * 3;

        primitives[i] = std::make_unique<Triangle>(
            vertices[faces[index]],
            vertices[faces[index + 1]],
            vertices[faces[index + 2]]);

        this->logger.trace(
            "\nTriangle {} composed of indices in range: [{}, {}]\n{}\n",
            i, index, index + 2, primitives[i]->toString());
    }

    return primitives;
}

// ============================================================================
// EOF
// ============================================================================