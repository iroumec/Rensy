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
import :pipeline.depth_test;
import :pipeline.framebuffer;
import :pipeline.interpolator;
import :pipeline.face_culling;
import :pipeline.rasterizer;
import :pipeline.shader.vertex;
import :primitive.topology.base;
import :pipeline.shader.fragment;
import :pipeline.shader.geometry;
import :pipeline.primitive_assembly;
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
        logger, inputData.lightingModel);

    std::vector<VertexOut> processedVertices =
        vertexShader.processVertices(vbo.vertices);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // PRIMITIVE ASSEMBLY
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    PrimitiveAssembler primitiveAssembler(logger);

    std::vector<std::unique_ptr<Primitive>> primitives =
        primitiveAssembler.assemblyPrimitives(processedVertices, ebo.faces);

    logger.debug("\n> Number of primitives assembled: {}", primitives.size());

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // GEOMETRY SHADER
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    GeometryShader geometryShader(
        logger, inputData.primitiveGenerator, inputData.lightingModel);
    geometryShader.processPrimitives(primitives);

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

    PerspectiveDivider perspectiveDivider(logger);

    for (auto &primitive : primitives)
        perspectiveDivider.applyPerspectiveDivision(*primitive);

    logger.debug("\n> Primitives after perspective divide: {}", primitives.size());

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // VIEWPORT TRANSFORM
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    ViewportTransformPhase viewportTransform(
        inputData.screenWidth, inputData.screenHeight, logger);

    for (auto &primitive : primitives)
        viewportTransform.processPrimitive(*primitive);

    logger.debug("\n> Primitives after viewport transform: {}", primitives.size());

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // RASTERIZATION
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    Rasterizer rasterizer(
        inputData.pointRasterizer,
        inputData.lineRasterizer,
        inputData.triangleRasterizer,
        inputData.screenWidth,
        inputData.screenHeight);

    std::vector<PreFragment> prefragments;

    for (const auto &primitive : primitives)
    {
        auto generated = rasterizer.rasterize(*primitive);

        prefragments.insert(
            prefragments.end(),
            std::make_move_iterator(generated.begin()),
            std::make_move_iterator(generated.end()));
    }

    logger.debug("\n> Prefragments after rasterization: {}", prefragments.size());

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // INTERPOLATION
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    Interpolator interpolator(inputData.colourCalculator, logger);

    std::vector<Fragment> fragments;
    fragments.reserve(prefragments.size());

    for (const PreFragment &prefragment : prefragments)
        fragments.push_back(interpolator.interpolate(prefragment));

    logger.debug("\n> Fragments after interpolation: {}", fragments.size());

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // FRAGMENT SHADER
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    FragmentShader fragmentShader(logger, inputData.lightingModel);

    fragmentShader.processFragments(fragments);

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
