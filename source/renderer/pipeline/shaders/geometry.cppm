module;

#include <vector>
#include <memory>

export module renderer:pipeline.shader.geometry;

// ============================================================================
// Imports
// ============================================================================

import :transform.mvp;
import :transform.view;
import :logging.logger;
import :transform.model;
import :colour.generator;
import :lighting.model.base;
import :structure.vertex_in;
import :structure.vertex_out;
import :transform.projection;
import :transform.projection;
import :primitive.generator.base;

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
    const Logger &logger;
    const ProjectionTransform &projectionTransform;
    const PrimitiveGenerator *primitiveGenerator;
    const LightingModel *lightingModel;

public:
    GeometryShader(
        const Logger &logger,
        const ProjectionTransform &projectionTransform,
        const PrimitiveGenerator *primitiveGenerator = nullptr,
        const LightingModel *lightingModel = nullptr)
        : logger{logger}, projectionTransform{projectionTransform},
          primitiveGenerator{primitiveGenerator}, lightingModel{lightingModel} {}

    void processPrimitives(
        std::vector<std::unique_ptr<Primitive>> &primitives) const;
};

// ============================================================================
// EOF
// ============================================================================
