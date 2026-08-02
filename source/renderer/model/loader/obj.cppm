module;

#include <tuple>
#include <string>

export module renderer:model.loader.obj;

// ============================================================================
// Imports
// ============================================================================

import vector;
import :structure.vbo;
import :structure.ebo;
import :model.loader.base;
import :normal.calculator;

// ============================================================================
// Declarations
// ============================================================================

export class ObjModelLoader : public ModelLoader
{
public:
    std::tuple<VBO, EBO> load(
        const std::string &filename,
        const NormalCalculator &normalCalculator) const override;
};

// ============================================================================
// EOF
// ============================================================================
