module;

#include <vector>

export module renderer:normal.calculator.file_extracted;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_in;
import :normal.calculator.base;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class FileExtractedNormalCalculator : public NormalCalculator
{

public:
    constexpr void calculateNormals(
        std::vector<VertexIn> &vertices,
        const std::vector<int> &faces) const override
    {
        // Does nothing.
        // Uses the normals already extracted by the model loader.
    }
};

// ============================================================================
// EOF
// ============================================================================