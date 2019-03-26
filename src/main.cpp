#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" // Full credit to Sean Barrett

struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

int main(int argc, const char **argv) {
    uint32_t w = std::stoi(argv[2]); // width
    uint32_t h = std::stoi(argv[2]); // height

    Pixel *data = new Pixel[w * h];
    uint32_t stride = w * sizeof(Pixel);
    for (uint32_t x = 0; x < w; x++) {
        for (uint32_t y = 0; y < h; y++) {
            data[y * w + x].r = x;
            data[y * w + x].g = y;
            data[y * w + x].b = x * y;
        }
    }
    stbi_write_png(argv[1], w, h, 3, data, stride);

    return 0;
}
