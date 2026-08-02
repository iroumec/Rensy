module;

#include <vector>
#include <iostream>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :pipeline.clipping;
import :structure.fragment;
import :structure.triangle;
import :pipeline.depth_test;
import :pipeline.framebuffer;
import :pipeline.vertex_shader;
import :pipeline.fragment_shader;
import :pipeline.primitive_assembly;
import :pipeline.viewport_transform;
import :pipeline.perspective_divide;

// ============================================================================
// Constants
// ============================================================================

constexpr bool VERBOSE = true;

// ============================================================================
// Declarations and Implementations
// ============================================================================

RenderingOutputData Renderer::
    render(const RenderingInputData &inputData)
{
    if (VERBOSE)
        std::cout
            << "\n| RENDERING PROCESS INITIATED |\n\n> Rendering model:"
            << inputData.fileName << '\n';

    // 1. Vertex Input.
    auto [vbo, ebo] =
        inputData.modelLoader.load(
            inputData.fileName, inputData.normalCalculator);

    if (VERBOSE)
        std::cout
            << "\n> Vertices received: " << vbo.vertices.size() << '\n';

    // 2. Vertex shader.
    std::vector<VertexOut> processedVertices = processVertices(
        vbo.vertices,
        inputData.modelTransform,
        inputData.viewTransform,
        inputData.projectionTransform,
        inputData.colourGenerator);

    // 3. Primitive Assembly.
    std::vector<Triangle> primitives =
        assemblyPrimitives(processedVertices, ebo.faces);

    if (VERBOSE)
        std::cout
            << "\n> Primitives assembled: " << primitives.size() << '\n';

    // 4. Clipping.
    // std::vector<Triangle> primitives = applyClipping(primitives);

    // 5. Perspective Divide.
    applyPerspectiveDivide(primitives);

    // 6. Viewport Transform.
    applyViewportTransform(
        primitives, inputData.screenWidth, inputData.screenHeight);

    // 7&8. Rasterization && Fragment Shader.
    std::vector<Fragment> fragments;
    FragmentShader fragmentShader(
        inputData.colourCalculator,
        inputData.colourShadingFactory);

    for (Triangle &primitive : primitives)
    {
        std::vector<Fragment> primitiveFragments =
            inputData.rasterizer.rasterize(
                primitive, inputData.screenWidth, inputData.screenHeight);

        fragmentShader.processFragments(primitiveFragments, primitive);

        fragments.insert(
            fragments.end(),
            primitiveFragments.begin(),
            primitiveFragments.end());
    }

    if (VERBOSE)
        std::cout
            << "\n> Fragments after rasterization: " << fragments.size() << '\n';

    // 9. Depth Test
    DepthBuffer zBuffer(inputData.screenWidth, inputData.screenHeight);
    std::vector<Fragment> processedFragments = zBuffer.process(fragments);

    if (VERBOSE)
        std::cout << "\n> Fragments after depth test: "
                  << processedFragments.size() << '\n';

    // 10. Stencil test.
    // TODO

    // 11. Blending.
    // TODO

    // 12. Framebuffer
    FrameBuffer frameBuffer(
        inputData.screenWidth, inputData.screenHeight, inputData.backgroundColour);
    frameBuffer.process(processedFragments);

    // 13. Post-Processing.
    if (inputData.filter != nullptr)
        inputData.filter->apply(frameBuffer, zBuffer);

    return RenderingOutputData{
        frameBuffer,
        zBuffer,
    };
}

// ============================================================================
// EOF
// ============================================================================
