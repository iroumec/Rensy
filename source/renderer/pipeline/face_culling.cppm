module;

#include <vector>
#include <stdexcept>

export module renderer:pipeline.face_culling;

// ============================================================================
// Imports
// ============================================================================

import :logging.logger;
import :primitive.topology.base;

// ============================================================================
// Declarations
// ============================================================================

export class FaceCuller
{
    const Logger &logger;

public:
    FaceCuller(const Logger &logger) : logger{logger} {}

    bool isVisible(const Primitive &primitive);
};

// ============================================================================
// EOF
// ============================================================================
