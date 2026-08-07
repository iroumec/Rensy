module;

#include <vector>

export module renderer:interpolation.data;

// ============================================================================
// Imports
// ============================================================================

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

    VertexOut getInterpolatedVertex() const
    {
        VertexOut vertex;

        for (const AttributeInfluence &influence : this->influences)
        {
            vertex += influence.getPonderatedVertex();
        }

        return vertex;
    }
};

// ============================================================================
// EOF
// ============================================================================