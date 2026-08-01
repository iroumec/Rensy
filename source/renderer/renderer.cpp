module;

#include <vector>

module renderer;

// ============================================================================
// Exports-Import
// ============================================================================

export import :depth_test;
export import :framebuffer;

// ============================================================================
// Imports
// ============================================================================

import vector;
import :clipping;
import :vertex_shader;
import :perspective_divide;
import :primitive_assembly;
import :viewport_transform;

// ============================================================================
// Declarations and Implementations
// ============================================================================

RenderingOutputData Renderer::
    render(const RenderingInputData &inputData) const
{
    // 2. Vertex shader.
    std::vector<VertexOut> processedVertices = processVertices(inputData);

    // 3. Primitive Assembly.
    std::vector<Triangle> primitives =
        assemblyPrimitives(processedVertices, inputData.faces);

    // 4. Clipping.
    // std::vector<Triangle> primitives = applyClipping(primitives);

    // 5. Perspective Divide.
    applyPerspectiveDivide(primitives);

    // 6. Viewport Transform.
    applyViewportTransform(
        primitives, inputData.screenWidth, inputData.viewWidth);

    // 7. Rasterization.

    std::vector<Fragment> fragments =
        inputData.rasterizer.rasterize(primitives);

    // 8. Fragment shader.
    // for (fragment : fragments)
    //    fragmentShader.apply(fragment);

    // 9. Depth Test
    DepthBuffer zBuffer(inputData.width, inputData.height);
    std::vector<Fragment> processedFragments = zBuffer.process(fragments);

    // 10. Stencil test.
    // TODO

    // 11. Blending.
    // TODO

    // 12. Framebuffer
    FrameBuffer frameBuffer(
        inputData.width, inputData.height, inputData.backgroundColour);
    frameBuffer.process(processedFragments);

    return RenderingOutputData{
        frameBuffer,
        zBuffer,
    };
}

// ============================================================================
// EOF
// ============================================================================
