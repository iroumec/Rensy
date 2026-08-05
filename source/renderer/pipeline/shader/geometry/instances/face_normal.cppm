module;

#include <vector>
#include <memory>

export module renderer:pipeline.shader.geometry.normal.face;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology.base;
import :pipeline.shader.geometry.base;

// ============================================================================
// Declarations
// ============================================================================

export class FaceNormalGeometryShader : public GeometryShader
{
    // Returns lines for the normals of the primitive.
    std::vector<std::unique_ptr<Primitive>> process(
        std::vector<std::unique_ptr<Primitive>> primitives) const override
    {
        // TODO.
        return primitives;
    }
};

// ============================================================================
// EOF
// ============================================================================