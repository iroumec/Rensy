module;

#include <vector>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :colour.calculator;
import :structure.fragment;
import :interpolation.data;
import :structure.prefragment;
import :pipeline.interpolator;

// ============================================================================
// Implementations
// ============================================================================

std::vector<Fragment> Interpolator::interpolate(
    const std::vector<PreFragment> &prefragments)
{
    std::vector<Fragment> out;
    out.reserve(prefragments.size());

    for (const PreFragment &prefragment : prefragments)
    {
        out.push_back(interpolate(prefragment, colourCalculator));
    }

    return out;
}

Fragment Interpolator::interpolate(const PreFragment &prefragment)
{
    Fragment fragment;
    fragment.xScreen = prefragment.xScreen;
    fragment.yScreen = prefragment.yScreen;
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