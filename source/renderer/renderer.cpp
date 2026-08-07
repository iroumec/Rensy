module;

#include <vector>
#include <memory>

module renderer;

// ============================================================================
// Imports
// ============================================================================

import :primitive;
import :logging.logger;
import :pipeline.clipping;
import :structure.fragment;
import :structure.triangle;
import :primitive.topology;
import :pipeline.depth_test;
import :pipeline.framebuffer;
import :pipeline.face_culling;
import :pipeline.interpolation;
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

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // VERTEX INPUT
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    auto [vbo, ebo] =
        inputData.modelLoader.load(
            inputData.fileName, inputData.normalCalculator);

    logger.debug("\n> Number of vertices loaded: {}", vbo.vertices.size());

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // VERTEX SHADER
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    VertexShader vertexShader(
        inputData.modelTransform, inputData.viewTransform,
        inputData.projectionTransform, inputData.colourGenerator,
        inputData.lightingModel);

    std::vector<VertexOut> processedVertices =
        vertexShader.processVertices(vbo.vertices);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // PRIMITIVE ASSEMBLY
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    std::vector<std::unique_ptr<Primitive>> primitives =
        assemblyPrimitives(processedVertices, ebo.faces);

    logger.debug("\n> Number of primitives assembled: {}", primitives.size());

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // GEOMETRY SHADER
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    GeometryShader geometryShader(inputData.primitiveGenerator);

    primitives = geometryShader.processPrimitives(primitives);

    logger.debug(
        "\n> Number of primitives after geometry shader: {}",
        primitives.size());

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // FACE CULLING
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // primitives = applyFaceCulling(primitives, logger);

    logger.debug("\n> Primitives after face culling: {}", primitives.size());

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // CLIPPING
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // std::vector<Triangle> primitives = applyClipping(primitives);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // PERSPECTIVE DIVIDE
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    applyPerspectiveDivide(primitives);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // VIEWPORT TRANSFORM
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    applyViewportTransform(
        primitives, inputData.screenWidth, inputData.screenHeight);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // RASTERIZATION
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    std::vector<PreFragment> prefragments = inputData.rasterizer.rasterize(
        primitives,
        inputData.screenWidth,
        inputData.screenHeight);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // INTERPOLATION
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    std::vector<Fragment> fragments = interpolate(
        prefragments, inputData.colourCalculator);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // FRAGMENT SHADER
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    FragmentShader fragmentShader(inputData.lightingModel);

    fragmentShader.processFragments(primitiveFragments, primitive);

    logger.debug("\n> Fragments after rasterization: {}", fragments.size());

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // DEPTH TEST
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    DepthBuffer zBuffer(inputData.screenWidth, inputData.screenHeight);
    std::vector<Fragment> processedFragments = zBuffer.process(fragments);

    logger.debug(
        "\n> Fragments after depth test: {}",
        processedFragments.size());

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STENCIL TEST
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // TODO

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // BLENDING
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // TODO

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // FRAMEBUFFER
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    FrameBuffer frameBuffer(
        inputData.screenWidth, inputData.screenHeight, inputData.backgroundColour);
    frameBuffer.process(processedFragments);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // POST-PROCESSING
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
