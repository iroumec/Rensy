#include <iostream>
#include <string>

import model;
import colour;
import buffer;
import tgaimage;
import rasterizer;
import configuration;
import matrix;

int main(int argc, char **argv)
{
    // Number of arguments check.
    if (argc < 2)
    {
        std::cerr << "A model must be passed as an argument." << std::endl;
        // std::cerr << "Usage: " << argv[0] << " obj/model.obj" << std::endl;
        return 1;
    }

    Model model{argv[1]};
    FrameBuffer buffer{width, height};
    // VertexRasterizer rasterizer;
    // WireframeRasterizer rasterizer;
    // ScanlineRasterizer rasterizer;
    BoundingBoxRasterizer rasterizer;

    Matrix<int, 2, 2> a{1, 2, 1, 2};
    Matrix<int, 2, 2> b{{1, 2}, {3, 4}};

    std::cout << a << std::endl
              << std::endl;

    std::cout << b << std::endl
              << std::endl;

    std::cout << a + b << std::endl
              << std::endl;

    std::cout << a - b << std::endl
              << std::endl;

    std::cout << a * b << std::endl
              << std::endl;

    std::cout << b.transpose() << std::endl
              << std::endl;

    Matrix<double, 2, 2> A{
        {1.0, 2.0},
        {3.0, 4.0}};

    std::cout << A << std::endl
              << std::endl;

    auto inv = A.inverse();
    std::cout << inv << std::endl
              << std::endl;

    auto I = A * inv;
    std::cout << I << std::endl
              << std::endl;

    RandomColourGenerator colourGenerator{randomSeed};

    rasterizer.draw(model, buffer, colourGenerator);

    buffer.renderColourBuffer(outputFrameFileName);
    buffer.renderDepthBuffer(outputZBufferFileName);
    return 0;
}
