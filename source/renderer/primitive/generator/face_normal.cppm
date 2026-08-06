module;

#include <vector>
#include <memory>

export module renderer:primitive.generator.normal.face;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology.base;
import :primitive.generator.base;

// ============================================================================
// Declarations
// ============================================================================

export class FaceNormalPrimitiveGenerator : public PrimitiveGenerator
{
    // Returns lines for the normals of the primitive.
    std::vector<std::unique_ptr<Primitive>> processPrimitives(
        std::vector<std::unique_ptr<Primitive>> primitives) const override
    {
        // TODO.
        return primitives;
    }
};

// ============================================================================
// EOF
// ============================================================================