module;

#include <vector>

export module renderer:pipeline.interpolation.data;

// ============================================================================
// Declarations
// ============================================================================

struct AttributeInfluence
{
    const VertexOut vertex;
    double weight;
};

struct InterpolationData
{
    std::vector<AttributeInfluence> influences;

    AttributeInfluence *getMaxInfluentialAttribute()
    {
        AttributeInfluence *maxInfluence = nullptr;

        for (const AttributeInfluence &influence : this->influences)
        {
            if (maxInfluence == nullptr ||
                (maxInfluence->weight < influence.weight))
                maxInfluence = &influence;
        }

        return maxInfluence;
    }

    AttributeInfluence *getMinInfluentialAttribute()
    {
        AttributeInfluence *minInfluence = nullptr;

        for (const AttributeInfluence &influence : this->influences)
        {
            if (minInfluence == nullptr ||
                (minInfluence->weight > influence.weight))
                minInfluence = &influence;
        }

        return minInfluence;
    }
};

// ============================================================================
// EOF
// ============================================================================