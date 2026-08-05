module;

#include <vector>

export module renderer:pipeline.primitive_assembly;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :primitive.topology.base;
import :primitive.topology.triangle;

// ============================================================================
// Declarations
// ============================================================================

export constexpr std::vector<Primitive> assemblyPrimitives(
    const std::vector<VertexOut> &vertices,
    const std::vector<int> &faces)
{
    int numberOfFaces = faces.size() / 3;

    std::vector<Primitive> primitives(numberOfFaces);

    // #pragma omp parallel for
    for (unsigned int i = 0; i < numberOfFaces; ++i)
    {
        // Each face is stored as three consecutive indices into the vertices array.
        // faceNumber * 3 gives the first index of the face, and vertexNumber (0-2)
        // selects one of its three vertices.

        // If faceNumber = 0, we are placed in the first face. Increasing vertexNumber
        // in [0, 2] gives us the vertex.
        VertexOut v0 = vertices[faces[i * 3 + 0]];
        VertexOut v1 = vertices[faces[i * 3 + 1]];
        VertexOut v2 = vertices[faces[i * 3 + 2]];
        primitives[i] = Triangle(v0, v1, v2);
    }

    return primitives;
}

// ============================================================================
// EOF
// ============================================================================