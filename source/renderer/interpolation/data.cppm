module;

#include <vector>
#include <cassert>

export module renderer:interpolation.data;

// ============================================================================
// Imports
// ============================================================================

import :logging.logger;
import :structure.vertex_out;

// ============================================================================
// Declarations
// ============================================================================

export struct AttributeInfluence
{
    const VertexOut vertex;
    double weight;

    VertexOut getPonderatedVertex() const
    {
        return this->vertex * this->weight;
    }
};

export struct InterpolationData
{
    std::vector<AttributeInfluence> influences;

    auto begin() const { return influences.begin(); }
    auto end() const { return influences.end(); }

    const AttributeInfluence *getMaxInfluentialAttribute() const
    {
        const AttributeInfluence *maxInfluence = nullptr;

        for (const AttributeInfluence &influence : this->influences)
        {
            if (!maxInfluence || maxInfluence->weight < influence.weight)
                maxInfluence = &influence;
        }

        return maxInfluence;
    }

    const AttributeInfluence *getMinInfluentialAttribute() const
    {
        const AttributeInfluence *minInfluence = nullptr;

        for (const AttributeInfluence &influence : this->influences)
        {
            if (!minInfluence || minInfluence->weight > influence.weight)
                minInfluence = &influence;
        }

        return minInfluence;
    }

    VertexOut getInterpolatedVertex(const Logger &logger) const
    {
        VertexOut vertex;

        logger.trace(
            "INTERPOLATOR: Vertex before interpolation: {}",
            vertex.toString());

        for (const AttributeInfluence &influence : this->influences)
        {
            assert(std::isfinite(influence.weight));
            assert(std::isfinite(influence.vertex.lightIntensity));

            VertexOut ponderated = influence.getPonderatedVertex();

            assert(std::isfinite(ponderated.lightIntensity));

            vertex += ponderated;

            assert(std::isfinite(vertex.lightIntensity));
        }

        logger.trace(
            "INTERPOLATOR: Vertex after interpolation: {}",
            vertex.toString());

        return vertex;
    }
};

// ============================================================================
// EOF
// ============================================================================