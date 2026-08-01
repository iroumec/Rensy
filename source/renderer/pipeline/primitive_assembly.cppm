module;

#include <vector>

export module renderer:pipeline.primitive_assembly;

// ============================================================================
// Imports
// ============================================================================

import :structure.triangle;
import :structure.vertex_out;

// ============================================================================
// Declarations
// ============================================================================

export constexpr std::vector<Triangle> assemblyPrimitives(
    const std::vector<VertexOut> &vertices,
    const std::vector<int> &faces)
{
    int numberOfFaces = faces.size() / 3;

    std::vector<Triangle> primitives(numberOfFaces);

    // #pragma omp parallel for
    for (unsigned int i = 0; i < numberOfFaces; ++i)
    {
        VertexOut v0 = vertices[faces[i * 3 + 0]];
        VertexOut v1 = vertices[faces[i * 3 + 1]];
        VertexOut v2 = vertices[faces[i * 3 + 2]];
        primitives[i] = Triangle{v0, v1, v2};
    }

    return primitives;
}

// ============================================================================
// EOF
// ============================================================================