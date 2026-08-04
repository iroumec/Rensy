module;

#include <vector>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :primitive;
import :logging.logger;
import :pipeline.clipping;
import :structure.fragment;
import :structure.triangle;
import :pipeline.depth_test;
import :pipeline.framebuffer;
import :pipeline.face_culling;
import :pipeline.vertex_shader;
import :pipeline.fragment_shader;
import :pipeline.viewport_transform;
import :pipeline.perspective_divide;

// ============================================================================
// Declarations and Implementations
// ============================================================================

RenderingOutputData Renderer::
    render(const RenderingInputData &inputData)
{
    Logger logger{inputData.logLevel};
    logger.info(
        "\n| RENDERING PROCESS INITIATED |\n\n> Rendering model: {}",
        inputData.fileName);

    // 1. Vertex Input.
    auto [vbo, ebo] =
        inputData.modelLoader.load(
            inputData.fileName, inputData.normalCalculator);

    logger.debug("\n> Number of vertices loaded: {}", vbo.vertices.size());

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

    logger.debug("\n> Number of primitives assembled: {}", primitives.size());

    // Geometry Shader.
    primitives = inputData.geometryShader.process(primitives);

    logger.debug("\n> Number of primitives after geometry shader: {}", primitives.size());

    // Face Culling.
    primitives = applyFaceCulling(primitives, logger);

    logger.debug("\n> Primitives after face culling: {}", primitives.size());

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
        inputData.shadingFactory);

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

    logger.debug("\n> Fragments after rasterization: {}", fragments.size());

    // 9. Depth Test
    DepthBuffer zBuffer(inputData.screenWidth, inputData.screenHeight);
    std::vector<Fragment> processedFragments = zBuffer.process(fragments);

    logger.debug(
        "\n> Fragments after depth test: {}",
        processedFragments.size());

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
