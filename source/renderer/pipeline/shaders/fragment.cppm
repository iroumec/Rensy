module;

#include <vector>

export module renderer:pipeline.shader.fragment;

// ============================================================================
// Imports
// ============================================================================

import :logging.logger;
import :colour.calculator;
import :structure.fragment;
import :lighting.model.base;

// ============================================================================
// Forward Declarations
// ============================================================================

// ============================================================================
// Declarations
// ============================================================================

export class FragmentShader
{
    const Logger &logger;
    const LightingModel *lightingModel;

public:
    FragmentShader(
        const Logger &logger, const LightingModel *lightingModel = nullptr)
        : logger{logger}, lightingModel(lightingModel) {}

    void processFragments(std::vector<Fragment> &fragments);
};

// ============================================================================
// EOF
// ============================================================================
