module;

#include <vector>

export module renderer:pipeline.shader.geometry.identity;

// ============================================================================
// Imports
// ============================================================================

import :structure.primitive;
import :pipeline.shader.geometry.base;

// ============================================================================
// Declarations
// ============================================================================

export class IdentityGeometryShader : public GeometryShader
{
    std::vector<Primitive> process(const Primitive &primitive) const override
    {
        // Returns the same primitives received.
    }
};

// ============================================================================
// EOF
// ============================================================================