module;

#include <vector>

export module renderer:pipeline.interpolation;

// ============================================================================
// Imports
// ============================================================================

import :colour.calculator;
import :structure.fragment;
import :structure.prefragment;
import :pipeline.interpolation.data;

// ============================================================================
// Declarations
// ============================================================================

std::vector<Fragment> interpolate(
    const std::vector<PreFragment> prefragments,
    const ColourCalculator &colourCalculator)
{
    std::vector<Fragment> out;
    out.reserve(prefragments.size());

    for (const PreFragment &prefragment : prefragments)
    {
        out.push_back(interpolate(prefragment, colourCalculator));
    }

    return out;
}

Fragment interpolate(
    const PreFragment &prefragment,
    const ColourCalculator &colourCalculator)
{
    Fragment fragment;
    fragment.xScreen = prefragment.x;
    fragment.yScreen = prefragment.y;
    VertexOut interpolatedVertex =
        prefragment.interpolationData.getInterpolatedVertex();

    fragment.depth = interpolatedVertex.screenPosition.z();
    fragment.worldPosition = interpolatedVertex.worldPosition;
    fragment.normal = interpolatedVertex.normal;
    fragment.colour.set(
        colourCalculator.calculateColour(prefragment.interpolationData));

    for (const AttributeInfluence &influence : prefragment.interpolationData)
        fragment.weights.push_back(attribute.weight);

    return fragment;
}

// ============================================================================
// EOF
// ============================================================================