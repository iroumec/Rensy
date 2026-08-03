module;

#include <vector>

export module renderer:normal.mapper;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_in;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class NormalMapper
{

public:
    virtual constexpr void calculateNormals(
        std::vector<VertexIn> &vertices,
        const std::vector<int> &faces) const = 0;
};

// ============================================================================
// EOF
// ============================================================================