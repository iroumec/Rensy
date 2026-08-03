module;

#include <vector>

export module renderer:normal.rasterizer.base;

// ============================================================================
// Imports
// ============================================================================

import :structure.triangle;
import :structure.fragment;

// ============================================================================
// Declarations
// ============================================================================

export class NormalRasterizer
{

public:
    virtual ~NormalRasterizer() = default;

    virtual constexpr void rasterizeNormals(
        const Triangle &primitive,
        std::vector<Fragment> &fragments) const = 0;
};

// ============================================================================
// EOF
// ============================================================================