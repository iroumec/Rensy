module;

#include <vector>
#include <memory>

export module renderer:pipeline.shader.geometry.identity;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology.base;
import :pipeline.shader.geometry.base;

// ============================================================================
// Declarations
// ============================================================================

export class IdentityGeometryShader : public GeometryShader
{
    std::vector<std::unique_ptr<Primitive>> process(
        std::vector<std::unique_ptr<Primitive>> primitives) const override
    {
        // Returns the same primitives received.
        return primitives;
    }
};

// ============================================================================
// EOF
// ============================================================================