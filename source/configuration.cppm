module;

#include <string>

export module configuration;

import radian;
import rotation;

export constexpr unsigned WIDTH = 800;
export constexpr unsigned HEIGHT = 800;
export constexpr unsigned RANDOM_SEED = 42;
export constexpr Rotation ROTATION = Rotation{Radian{}, Radian::fromDegrees(30.0), Radian{}};
export constexpr std::string outputZBufferFileName = "zbuffer.tga";
export constexpr std::string outputFrameFileName = "framebuffer.tga";