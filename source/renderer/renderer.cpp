module;

#include <cmath>
#include <array>
#include <utility>
#include <ostream>
#include <vector>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import vector;

// ============================================================================
// Declarations and Implementations
// ============================================================================

RenderingOutputData Renderer::
    render(const RenderingInputData &inputData) const
{
    int numberOfVertices = inputData.vertices.size();

    std::vector<VertexOut> vertices(numberOfVertices);

    // 2. Vertex shader.
    // #pragma omp parallel for
    for (unsigned i = 0; i < numberOfVertices; i++)
        vertices[i] = VertexShader::processVertex(
            VertexIn{inputData.vertices[i], colourGenerator()});

    // 3. Primitive Assembly.
    std::vector<Triangle> primitives =
        assemblyPrimitives(inputData.vertices, inputData.faces);

    // 4. Clipping.
    // std::vector<Triangle> primitives = applyClipping(primitives);

    // 5. Perspective Divide.
    // #pragma omp parallel for
    for (primitive : primitives)
    {
        perspectiveDivide(primitive.v0);
        perspectiveDivide(primitive.v1);
        perspectiveDivide(primitive.v2);
    }

    // 6. Viewport Transform.
    // #pragma omp parallel for
    for (primitive : primitives)
    {
        applyViewportTransform(primitive.v0);
        applyViewportTransform(primitive.v1);
        applyViewportTransform(primitive.v2);
    }

    // 7. Rasterization.

    std::vector<Fragment> fragments;

    // #pragma omp parallel for
    for (primitive : primitives)
    {
        fragments.push(rasterizer.generateFragments(primitive));
    }

    // 8. Fragment shader.
    for (fragment : fragments)
        fragmentShader.apply(fragment);

    // 9. Depth Test

    std::vector<Fragment> finalFragments;

    for (fragment : fragments)
        if (depthTest.testAndSet(fragment))
            finalFragments.push_back(fragment);

    // 10. Stencil test.
    // TODO

    // 11. Blending.
    // TODO

    // 12. Framebuffer
    // #pragma omp parallel for
    for (fragment : finalFragments)
        framebuffer.setColour(fragment.x(), fragment.y(), fragment.colour());
}

// ============================================================================
// EOF
// ============================================================================
