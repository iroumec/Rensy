import colours;
import tgaimage;
import geometry;
import configuration;
import triangle_rasterizer;

void testBoundingBoxRasterizer()
{
    TGAImage framebuffer(width, height, TGAImage::RGB);
    TriangleRasterizer *rasterizer = new BoundingBoxTriangleRasterizer();

    rasterizer->draw(vec2{7, 45}, vec2{35, 100}, vec2{45, 60}, framebuffer, red);
    rasterizer->draw(vec2{120, 35}, vec2{90, 5}, vec2{45, 110}, framebuffer, white);
    rasterizer->draw(vec2{115, 83}, vec2{80, 90}, vec2{85, 120}, framebuffer, green);
    rasterizer->draw(vec2{10, 10}, vec2{40, 10}, vec2{20, 40}, framebuffer, blue);
    rasterizer->draw(vec2{150, 120}, vec2{180, 120}, vec2{165, 90}, framebuffer, yellow);
    rasterizer->draw(vec2{200, 110}, vec2{230, 30}, vec2{250, 100}, framebuffer, cyan);
    rasterizer->draw(vec2{270, 120}, vec2{274, 30}, vec2{280, 118}, framebuffer, magenta);
    rasterizer->draw(vec2{300, 90}, vec2{340, 88}, vec2{320, 92}, framebuffer, orange);
    rasterizer->draw(vec2{360, 30}, vec2{370, 75}, vec2{362, 120}, framebuffer, purple);

    // drawer.renderTGAImage(outputFileName);
    framebuffer.write_tga_file(outputFileName);
}