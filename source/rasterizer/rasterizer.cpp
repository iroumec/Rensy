module;

#include <cmath>
#include <iostream>
#include <algorithm>

module rasterizer;

import bbox;
import model;
import buffer;
import colour;
import vector;
import vertex;
import geometry;
import transform;
import perspective;
import barycentric;

constexpr bool DEBUG = false;

void Rasterizer::draw(const Model &model, FrameBuffer &framebuffer, const ColourGenerator &colourGenerator, const Rotation &rotation = Rotation{})
{

    MVPTransform mvpTransform{ModelTransform{RotationTransform{rotation}} /*, ProjectionTransform{1, 10}*/};
    ViewportTransform viewportTransform(framebuffer.getWidth(), framebuffer.getHeight());

    // Iterates through all triangles and draw them.
    for (unsigned i = 0; i < model.getNumberOfFaces(); i++)
    {
        Vector3D a = viewportTransform.apply(constantPerspectiveDivide(mvpTransform.apply(model.getVertex(i, 0))));
        Vector3D b = viewportTransform.apply(constantPerspectiveDivide(mvpTransform.apply(model.getVertex(i, 1))));
        Vector3D c = viewportTransform.apply(constantPerspectiveDivide(mvpTransform.apply(model.getVertex(i, 2))));
        this->draw({a, colourGenerator()}, {b, colourGenerator()}, {c, colourGenerator()}, framebuffer);
    }
}

void VertexRasterizer::draw(Vertex a, Vertex b, Vertex c, FrameBuffer &framebuffer)
{
    framebuffer.setColour(a.x(), a.y(), a.getColour());
    framebuffer.setColour(b.x(), b.y(), b.getColour());
    framebuffer.setColour(c.x(), c.y(), c.getColour());
}

void WireframeRasterizer::drawLine(Vertex a, Vertex b, FrameBuffer &framebuffer)
{
    /// Bresenham's line algorithm (variant with barycentric coordinates).
    // Is the line more vertical than horizontal?
    bool steep = std::abs(a.x() - b.x()) < std::abs(a.y() - b.y());
    if (steep)
    { // If that's the case, the image is transposed.
        std::swap(a.x(), a.y());
        std::swap(b.x(), b.y());
    }

    // Due to x increasing in the below loop, and it starting
    // at ax, it cannot draw right-to-left lines.
    if (a.x() > b.x())
    { // Make it left-to-right.
        std::swap(a.x(), b.x());
        std::swap(a.y(), b.y());
    }

    for (int x = a.x(); x <= b.x(); ++x)
    {
        int y = round(interpolateY(a.getVector(), b.getVector(), x));
        if (steep)                                      // If the image was transposed, it's de-transposed.
            framebuffer.setColour(y, x, a.getColour()); // TODO: Change the colour generation.
        else
            framebuffer.setColour(x, y, a.getColour()); // TODO: Change the oclpur generation.
    }
}

void WireframeRasterizer::draw(Vertex a, Vertex b, Vertex c, FrameBuffer &framebuffer)
{
    // This order is important for circular colour generators.
    this->drawLine(a, b, framebuffer);
    this->drawLine(c, a, framebuffer);
    this->drawLine(b, c, framebuffer);
}

void ScanlineRasterizer::draw(Vertex a, Vertex b, Vertex c, FrameBuffer &framebuffer)
{
    // Vertices ordering.
    auto orderedVertices = orderByAscendingAxisY(a, b, c);

    Vertex top = orderedVertices[2];
    Vertex middle = orderedVertices[1];
    Vertex bottom = orderedVertices[0];

    if (DEBUG)
    {
        std::cout << "Top: " << top << std::endl;
        std::cout << "Middle: " << middle << std::endl;
        std::cout << "Bottom: " << bottom << std::endl;
    }

    // The triangle is scanned row by row (scanline).
    // Each value of y is a scanline.
    // The scanning can be top to bottom or bottom to top.
    for (unsigned y = bottom.y(); y <= top.y(); y++)
    {

        // Implementation logic in documentation/drawings/scanline.excalidraw.
        // For Y, which Xleft and Xright closures the segment of the triangle?
        unsigned rightX = interpolateX(bottom.getVector(), top.getVector(), y);
        unsigned leftX = (middle.y() == top.y() || middle.y() > y)
                             ? interpolateX(bottom.getVector(), middle.getVector(), y)
                             : interpolateX(middle.getVector(), top.getVector(), y);
        if (middle.x() > top.x())
            std::swap(leftX, rightX);

        if (DEBUG)
        {
            std::cout << "leftX: " << leftX << std::endl;
            std::cout << "rightX: " << rightX << std::endl;
        }

        // The segment is painted.
        for (unsigned x = leftX; x <= rightX; x++)
            framebuffer.setColour(x, y, top.getColour()); // TODO: Fix this.
    }
}

void BoundingBoxRasterizer::draw(Vertex a, Vertex b, Vertex c, FrameBuffer &framebuffer)
{
    BoundingBox bbox = BoundingBox(a.getVector(), b.getVector(), c.getVector());

    double min = std::min(a.z(), std::min(b.z(), c.z()));
    double max = std::max(a.z(), std::max(b.z(), c.z()));

    for (unsigned y = bbox.minY; y <= bbox.maxY; y++)
    {
        for (unsigned x = bbox.minX; x <= bbox.maxX; x++)
        {
            BarycentricCoordinate coordinates = getBarycentricCoordinates(a.getVector(), b.getVector(), c.getVector(), Vector2D{(double)x, (double)y});
            if (!coordinates.isInsideTriangle())
                continue; // Outside the triangle.
            if (drawingPattern != nullptr && !drawingPattern->isValid(coordinates))
                continue;
            double z = coordinates.alpha * a.z() + coordinates.beta * b.z() + coordinates.gamma * c.z();
            if (framebuffer.isStoredDepthLower(x, y, z))
                continue;
            unsigned char zColour = static_cast<unsigned char>((z - min) / (max - min) * 255);
            // framebuffer.setColour(x, y, Colour{zColour, zColour, zColour, 255});
            Colour colour = this->colourCalculator.calculateColour(a, b, c, coordinates);
            if (colourIntensifier != nullptr)
                colour = colourIntensifier->adjustColour(colour, coordinates);
            framebuffer.setColour(x, y, colour);
            framebuffer.setDepth(x, y, z);
        }
    }
}