module;

#include <vector>
#include <memory>

export module renderer:pipeline.primitive_assembly;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology.base;

// ============================================================================
// Forward Declarations
// ============================================================================

class Logger;
struct VertexOut;

// ============================================================================
// Declarations
// ============================================================================

export class PrimitiveAssembler
{
    const Logger &logger;

public:
    PrimitiveAssembler(const Logger &logger)
        : logger{logger} {}

    std::vector<std::unique_ptr<Primitive>> assemblyPrimitives(
        const std::vector<VertexOut> &vertices,
        const std::vector<int> &faces) const;
};

// ============================================================================
// EOF
// ============================================================================