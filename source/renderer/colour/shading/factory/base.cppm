module;

#include <memory>

export module renderer:colour.shading.factory.base;

// ============================================================================
// Imports
// ============================================================================

import :primitive.topology;
import :colour.shading.instance.base;

// ============================================================================
// Declarations
// ============================================================================

export class ShadingFactory
{

public:
    virtual ~ShadingFactory() = default;

    virtual std::shared_ptr<Shading> instance(
        const Primitive &primitive) const = 0;
};

// ============================================================================
// EOF
// ============================================================================