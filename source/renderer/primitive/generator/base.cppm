module;

#include <memory>

export module renderer:primitive.generator.base;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology.base;

// ============================================================================
// Declarations
// ============================================================================

export class PrimitiveGenerator
{
public:
    // The ownership of the list of primitives is transferred.
    virtual std::vector<std::unique_ptr<Primitive>> processPrimitives(
        std::vector<std::unique_ptr<Primitive>> primitives) const = 0;
};

// ============================================================================
// EOF
// ============================================================================