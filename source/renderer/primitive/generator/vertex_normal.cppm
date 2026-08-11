module;

#include <vector>
#include <memory>
#include <iterator>
#include <iostream>

export module renderer:primitive.generator.normal.vertex;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :primitive.topology.base;
import :primitive.topology.line;
import :primitive.generator.base;

// ============================================================================
// Declarations
// ============================================================================

export class VertexNormalPrimitiveGenerator : public PrimitiveGenerator
{
    const double normalDistance;
    const Colour normalColour;

public:
    VertexNormalPrimitiveGenerator(
        double normalDistance, const Colour &normalColour)
        : normalDistance(normalDistance), normalColour(normalColour) {}

    // Returns lines for the normals of the primitive vertices.
    // For example, triangle -> 3 lines.
    void processPrimitives(
        std::vector<std::unique_ptr<Primitive>> &primitives) const override
    {
        std::vector<std::unique_ptr<Primitive>> generated;

        for (const auto &primitive : primitives)
            for (const VertexOut &vertex : primitive->getVertices())
            {
                // See resources/documentation/drawings/normalDrawing.
                const Vector3D startPosition = vertex.viewPosition;
                const Vector3D normal = vertex.viewNormal.normalize();
                const Vector3D endPosition =
                    startPosition + normal * normalDistance;

                VertexOut start = vertex;
                VertexOut end = vertex;

                start.viewPosition = startPosition;
                end.viewPosition = endPosition;

                start.colour.set(normalColour);
                end.colour.set(normalColour);

                // Colour locking.
                start.colour.lock();
                end.colour.lock();

                generated.push_back(std::make_unique<Line>(start, end));
            }

        // The space is reserved so reallocations are avoided.
        primitives.reserve(primitives.size() + generated.size());

        primitives.insert(
            primitives.end(),
            std::make_move_iterator(
                generated.begin()),
            std::make_move_iterator(
                generated.end()));
    }
};

// ============================================================================
// EOF
// ============================================================================