module;

#include <vector>
#include <memory>

export module renderer:primitive.generator.normal.face;

// ============================================================================
// Imports
// ============================================================================

import :structure.vertex_out;
import :primitive.topology.line;
import :primitive.topology.base;
import :primitive.generator.base;

// ============================================================================
// Declarations
// ============================================================================

export class FaceNormalPrimitiveGenerator : public PrimitiveGenerator
{
    const double normalDistance;
    const Colour normalColour;

public:
    FaceNormalPrimitiveGenerator(
        double normalDistance, const Colour &normalColour)
        : normalDistance(normalDistance), normalColour(normalColour) {}

    // Returns lines for the normals of the primitive vertices.
    // For example, triangle -> 3 lines.
    void processPrimitives(
        std::vector<std::unique_ptr<Primitive>> &primitives) const override
    {
        /*
        std::vector<std::unique_ptr<Primitive>> generated;

        for (const auto &primitive : primitives)
        {
            // See resources/documentation/drawings/normalDrawing.
            const Vector3D startPosition = primitive.getCentroid();
            const Vector3D normal = primitive.getRepresentativeNormal().normalize();
            const Vector3D endPosition =
                startPosition + normal * normalDistance;

            VertexOut start = vertex;
            VertexOut end = vertex;

            start.worldPosition = startPosition;
            end.worldPosition = endPosition;

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
            std::make_move_iterator(generated.begin()),
            std::make_move_iterator(generated.end()));
            */
    }
};

// ============================================================================
// EOF
// ============================================================================