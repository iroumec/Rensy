module;

#include <memory>

export module renderer:pipeline.shader.geometry.base;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology.base;

// ============================================================================
// Declarations
// ============================================================================

export class GeometryShader
{
public:
    // The ownership of the list of primitives is transferred.
    virtual std::vector<std::unique_ptr<Primitive>> process(
        std::vector<std::unique_ptr<Primitive>> primitives) const = 0;
};

// ============================================================================
// EOF
// ============================================================================