module;

#include <vector>

export module renderer:normal.calculator.base;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_in;

// ============================================================================
// Declarations
// ============================================================================

export class NormalCalculator
{

public:
    virtual ~NormalCalculator() = default;

    virtual constexpr void calculateNormals(
        std::vector<VertexIn> &vertices,
        const std::vector<int> &faces) const = 0;
};

// ============================================================================
// EOF
// ============================================================================