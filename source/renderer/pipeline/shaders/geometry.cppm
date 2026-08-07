module;

#include <vector>
#include <memory>

export module renderer:pipeline.shader.vertex;

// ============================================================================
// Imports
// ============================================================================

import :transform.mvp;
import :transform.view;
import :transform.model;
import :colour.generator;
import :structure.vertex_in;
import :structure.vertex_out;
import :transform.projection;

// ============================================================================
// Declarations
// ============================================================================

// The task done by the geometry shader is called "primitive generation" or
//   "geometry processing".
// However, different terms are used for it:
// - Primitive generation: the most general term. The geometry shader generates
//     zero, one or multiple primitives from one entry primitive.
// - Primitive amplification: when the number of output primitives is greater
//     than the number of input primitives.
// - Primitive reduction: when the number of output primitives is less than the
//     the number of input primitives or the same. (The discarding is called
//     culling).
// - Geometry expansion: informal term for primitive amplification.
export class GeometryShader
{
    const PrimitiveGenerator *primitiveGenerator;
    const LightingModel *lightingModel;

public:
    GeometryShader(
        const PrimitiveGenerator *primitiveGenerator = nullptr,
        const LightingModel *lightingModel = nullptr)
        : primitiveGenerator{primitiveGenerator}, lightingModel{lightingModel} {}

    std::vector<std::unique_ptr<Primitive>> processPrimitives(
        std::vector<std::unique_ptr<Primitive>> primitives) const;

    // ============================================================================
    // EOF
    // ============================================================================
