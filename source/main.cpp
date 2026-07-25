#include <iostream>
#include <string>

import model;
import drawer;
import tgaimage;
import geometry;

// BGRA.
constexpr TGAColour white = {255, 255, 255, 255};
constexpr TGAColour green = {0, 255, 0, 255};
constexpr TGAColour red = {0, 0, 255, 255};
constexpr TGAColour blue = {255, 0, 0, 255};
constexpr TGAColour yellow = {0, 255, 255, 255};
constexpr TGAColour cyan = {255, 255, 0, 255};
constexpr TGAColour magenta = {255, 0, 255, 255};
constexpr TGAColour orange = {0, 165, 255, 255};
constexpr TGAColour purple = {128, 0, 128, 255};

constexpr unsigned width = 380;
constexpr unsigned height = 140;
constexpr std::string outputFileName = "framebuffer.tga";

int main(int argc, char **argv)
{
    // Number of arguments check.
    if (argc < 2)
    {
        std::cerr << "A model must be passed as an argument." << std::endl;
        // std::cerr << "Usage: " << argv[0] << " obj/model.obj" << std::endl;
        return 1;
    }

    // Model model{argv[1]};
    Drawer drawer{height, width};

    // drawer.drawModel(model, red, white);

    drawer.drawFilledTriangle(vec2{7, 45}, vec2{35, 100}, vec2{45, 60}, red);
    drawer.drawFilledTriangle(vec2{120, 35}, vec2{90, 5}, vec2{45, 110}, white);
    drawer.drawFilledTriangle(vec2{115, 83}, vec2{80, 90}, vec2{85, 120}, green);
    drawer.drawFilledTriangle(vec2{10, 10}, vec2{40, 10}, vec2{20, 40}, blue);
    drawer.drawFilledTriangle(vec2{150, 120}, vec2{180, 120}, vec2{165, 90}, yellow);
    drawer.drawFilledTriangle(vec2{200, 110}, vec2{230, 30}, vec2{250, 100}, cyan);
    drawer.drawFilledTriangle(vec2{270, 120}, vec2{274, 30}, vec2{280, 118}, magenta);
    drawer.drawFilledTriangle(vec2{300, 90}, vec2{340, 88}, vec2{320, 92}, orange);
    drawer.drawFilledTriangle(vec2{360, 30}, vec2{370, 75}, vec2{362, 120}, purple);

    drawer.renderTGAImage(outputFileName);
    return 0;
}
