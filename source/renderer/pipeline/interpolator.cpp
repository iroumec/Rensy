module;

#include <vector>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :colour.calculator;
import :structure.fragment;
import :interpolation.data;
import :structure.vertex_out;
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
        out.push_back(interpolate(prefragment));
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
    fragment.normal = interpolatedVertex.worldNormal;
    fragment.colour.set(
        colourCalculator.calculateColour(prefragment.interpolationData));

    return fragment;
}

// ============================================================================
// EOF
// ============================================================================