module;

#include <cmath>
#include <array>
#include <utility>
#include <ostream>

export module vertex_shader;

// ============================================================================
// Imports
// ============================================================================

import vector;
import vertex_in;
import vertex_out;

// ============================================================================
// Declarations and Implementations
// ============================================================================

export class VertexShader
{

public:
    static VertexOut processVertex(cont VertexIn &vertexIn, const MVPTransform &mvpTransform)
    {
        return VertexOut{mvpTransform.apply(vertexIn.localPosition()), Vector3D{}, vertexIn.colour};
    }
};

void Rasterizer::draw(
    const Model &model,
    FrameBuffer &buffer,
    const ColourGenerator &colourGenerator,
    const MVPTransform &mvpTransform) const
{

    ViewportTransform viewportTransform(buffer.getWidth(), buffer.getHeight());

    // Iterates through all triangles and draw them.
    for (unsigned i = 0; i < model.getNumberOfFaces(); i++)
    {
        // Model coordinates.
        Vector4D v0Local(model.getVertex(i, 0));
        Vector4D v1Local(model.getVertex(i, 1));
        Vector4D v2Local(model.getVertex(i, 2));

        if (DEBUG)
        {
            std::cout << "v0Local: " << v0Local << std::endl;
            std::cout << "v1Local: " << v1Local << std::endl;
            std::cout << "v2Local: " << v2Local << std::endl;
        }

        // Transformation to homogeneous clip space.
        Vector4D v0Clip = mvpTransform.apply(v0Local);
        Vector4D v1Clip = mvpTransform.apply(v1Local);
        Vector4D v2Clip = mvpTransform.apply(v2Local);

        if (DEBUG)
        {
            std::cout << "v0Clip: " << v0Clip << std::endl;
            std::cout << "v1Clip: " << v1Clip << std::endl;
            std::cout << "v2Clip: " << v2Clip << std::endl;
        }

        // Clipping space validation.
        if (true /*insideClipVolume(v0Clip) &&
            insideClipVolume(v1Clip) &&
            insideClipVolume(v2Clip)*/
                 /* v0Clip.w() > 0.001 &&
             v1Clip.w() > 0.001 && v2Clip.w() > 0.001 */
        )
        {
            // Screen space transformation (NDC -> Viewport).
            Vector4D v0Viewport = viewportTransform.apply(getNDC(v0Clip));
            Vector4D v1Viewport = viewportTransform.apply(getNDC(v1Clip));
            Vector4D v2Viewport = viewportTransform.apply(getNDC(v2Clip));

            if (DEBUG)
            {
                std::cout << "v0Viewport: " << v0Viewport << std::endl;
                std::cout << "v1Viewport: " << v1Viewport << std::endl;
                std::cout << "v2Viewport: " << v2Viewport << std::endl;
            }

            this->draw(
                {v0Clip, v0Viewport, colourGenerator()},
                {v1Clip, v1Viewport, colourGenerator()},
                {v2Clip, v2Viewport, colourGenerator()},
                buffer);
        }
    }
}