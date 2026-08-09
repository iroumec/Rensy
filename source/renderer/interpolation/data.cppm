module;

#include <cmath>
#include <limits>
#include <vector>
#include <cstdlib>
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

        for (const AttributeInfluence &influence : this->influences)
        {
            if (!std::isfinite(influence.weight)) // Take this to a metod with a condition.
            {
                logger.error("Invalid weight: {}", influence.weight);
                std::abort();
            }

            if (!std::isfinite(influence.vertex.lightIntensity))
            {
                logger.error(
                    "Invalid input lightIntensity: {}",
                    influence.vertex.lightIntensity);
                std::abort();
            }

            VertexOut ponderated = influence.getPonderatedVertex();

            if (!std::isfinite(ponderated.lightIntensity))
            {
                logger.error(
                    "Invalid ponderated lightIntensity: {}",
                    ponderated.lightIntensity);
                std::abort();
            }

            vertex += ponderated;

            if (!std::isfinite(vertex.lightIntensity))
            {
                logger.error(
                    "Invalid accumulated lightIntensity: {}",
                    vertex.lightIntensity);
                std::abort();
            }
        }

        return vertex;
    }
};

// ============================================================================
// EOF
// ============================================================================