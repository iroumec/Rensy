
Fragment interpolate(const PreFragment &pre)
{
    Fragment fragment;
    fragment.xScreen = pre.x;
    fragment.yScreen = pre.y;
    VertexOut interpolatedVertex = pre.interpolationData.getInterpolatedVertex();

    fragment.depth = interpolatedVertex.screenPosition.z();
    fragment.worldPosition = interpolatedVertex.worldPosition;
    fragment.normal = interpolatedVertex.normal;
    fragment.colour.set(interpolatedVertex.colour.get()); // TODO: Put colour calculator here.

    for (const AttributeInfluence &influence : pre.interpolationData.influences)
        fragment.weights.push_back(attribute.weight);

    return fragment;
}