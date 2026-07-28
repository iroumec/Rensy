module;

#include <memory>
#include <string>

export module configuration;

import radian;
import colour;
import pattern;
import rotation;

export constexpr unsigned WIDTH = 1080;
export constexpr unsigned HEIGHT = 1080;
export constexpr unsigned RANDOM_SEED = 42;
export const RandomColourGenerator COLOUR_GENERATOR{RANDOM_SEED};
// export const StaticColourGenerator COLOUR_GENERATOR{red};
export constexpr Rotation ROTATION = Rotation{Radian{}, Radian::fromDegrees(30.0), Radian{}};
export constexpr std::string outputZBufferFileName = "zbuffer.tga";
export constexpr std::string outputFrameFileName = "framebuffer.tga";
export const BorderDrawingPattern BORDER_DRAWING_PATTERN{};
export const CenterDrawingPattern CENTER_DRAWING_PATTERN{};
// export const Pattern *PATTERN = &BORDER_PATTERN;
export const DrawingPattern *DRAWING_PATTERN = nullptr;
export const BorderColourPattern BORDER_COLOUR_PATTERN{};
export const CenterColourPattern CENTER_COLOUR_PATTERN{};
export const ColourPattern *COLOUR_PATTERN = &CENTER_COLOUR_PATTERN;