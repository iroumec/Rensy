module;

#include <vector>

export module renderer:pipeline.shader.geometry.normal;

// ============================================================================
// Imports
// ============================================================================

import :structure.primitive;
import :pipeline.shader.geometry.base;

// ============================================================================
// Declarations
// ============================================================================

export class FaceNormalGeometryShader : public GeometryShader
{
    // Returns lines for the normals of the primitive.
    std::vector<Primitive> process(const Primitive &primitive) const override
    {
        // Returns the same primitives received.
    }
};

// ============================================================================
// EOF
// ============================================================================