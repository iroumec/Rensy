module;

#include <vector>
#include <memory>

export module renderer:pipeline.shader.geometry.normal.vertex;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :primitive.topology.base;
import :primitive.topology.line;
import :pipeline.shader.geometry.base;

// ============================================================================
// Declarations
// ============================================================================

export class VertexNormalGeometryShader : public GeometryShader
{
    const double normalDistance;
    const Colour normalColour;

public:
    VertexNormalGeometryShader(
        double normalDistance, const Colour &normalColour)
        : normalDistance(normalDistance), normalColour(normalColour) {}

    // Returns lines for the normals of the primitive vertices.
    // For example, triangle -> 3 lines.
    std::vector<std::unique_ptr<Primitive>> process(
        std::vector<std::unique_ptr<Primitive>> primitives) const override
    {
        std::vector<std::unique_ptr<Primitive>> out;

        for (const auto &primitive : primitives)
        {
            for (const VertexOut &vertex : primitive->vertices())
            {
                // See resources/documentation/drawings/normalDrawing.
                VertexOut start = vertex;
                VertexOut end = vertex;

                end.worldPosition =
                    start.worldPosition + start.worldNormal.normalize() * normalDistance;

                start.colour.set(normalColour);
                end.colour.set(normalColour);

                // Colour locking.
                start.colour.lock();
                end.colour.lock();

                out.push_back(std::make_unique<Line>(start, end));
            }

            out.push_back(primitive->clone());
        }

        return out;
    }
};

// ============================================================================
// EOF
// ============================================================================