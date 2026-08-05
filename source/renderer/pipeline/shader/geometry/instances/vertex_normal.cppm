module;

#include <vector>

export module renderer:pipeline.shader.geometry.normal.vertex;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :primitive.topology.base;
import :pipeline.shader.geometry.base;

// ============================================================================
// Declarations
// ============================================================================

export class VertexNormalGeometryShader : public GeometryShader
{
    const double normalDistance;
    const Colour normalColour;

public:
    // Returns lines for the normals of the primitive vertices.
    // For example, triangle -> 3 lines.
    std::vector<Primitive> process(const Primitive &primitive) const override
    {
        std::vector<Primitive> out;

        for (const Primitive &primitive : primitives)
        {
            for (const VertexOut &vertex : primitive.vertices())
            {
                // See resources/documentation/drawings/normalDrawing.
                VertexOut start = vertex;
                VertexOut end = vertex;

                end.worldPosition = start.worldPosition + start.worldNormal.normalize() * normalDistance;

                start.colour.set(normalColour);
                end.colour.set(normalColour);

                // Colour locking.
                start.colour.lock();
                end.colour.lock();

                out.push_back(Line(start, end));
            }

            out.push_back(primitive);
        }

        return out;
    }
};

// ============================================================================
// EOF
// ============================================================================