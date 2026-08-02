module;

#include <tuple>
#include <string>

export module renderer:model.loader.base;

// ============================================================================
// Imports
// ============================================================================

import :structure.vbo;
import :structure.ebo;
import :normal.calculator;

// ============================================================================
// Declarations
// ============================================================================

export class ModelLoader
{
public:
    virtual std::tuple<VBO, EBO> load(
        const std::string &filename,
        const NormalCalculator &normalCalculator) const = 0;
};

// ============================================================================
// EOF
// ============================================================================