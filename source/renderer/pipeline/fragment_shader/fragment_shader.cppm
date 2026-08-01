module;

#include <vector>

export module renderer:pipeline.fragment_shader;

// ============================================================================
// Imports
// ============================================================================

import :structure.fragment;
import :structure.triangle;

// ============================================================================
// Declarations
// ============================================================================

export class FragmentShader
{

public:
    void processFragments(
        std::vector<Fragment> &fragments, const Triangle &primitive);
};

// ============================================================================
// EOF
// ============================================================================
