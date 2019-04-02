#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "catch.hpp"
#include "mat44.hpp"
#include "ray.hpp"
#include "stb_image_write.h"
#include <cstdlib>

struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct Camera {
    Mat44 camToWorld;
    uint32_t width;
    uint32_t height;
    float fov;
};

// clamps value to low <= value <= high
inline float clamp(const float &low, const float &high, const float &value) {
    return std::max(low, std::min(high, value));
}

// converts from degrees to radians
inline float deg2rad(const float &deg) { return deg * M_PI / 180; }

Pixel castRay(const Vec3 &orig, const Vec3 &dir, Camera &cam) {
    Vec3 hitColor = (dir + Vec3(1, 1, 1)) * 0.5;
    Pixel hit;
    hit.r = 255 * clamp(0, 1, hitColor.x);
    hit.g = 255 * clamp(0, 1, hitColor.y);
    hit.b = 255 * clamp(0, 1, hitColor.z);
    return hit;
}

Pixel *render(Camera &cam) {
    Pixel *frameBuffer = new Pixel[cam.width * cam.height];
    uint32_t stride = cam.width * sizeof(Pixel);
    float scale = tan(deg2rad(cam.fov * 0.5));
    float imageAspectRatio = cam.width / (float)cam.height;
    Vec3 orig = cam.camToWorld.transformPoint(Vec3());

    for (uint32_t j = 0; j < cam.height; j++) {
        for (uint32_t i = 0; i < cam.width; i++) {
#ifdef MAYA_MODE
            float x = (2 * (i + 0.5) / (float)cam.width - 1) * scale;
            float y = (1 - 2 * (j + 0.5) / (float)cam.width) * scale * 1 /
                      imageAspectRatio;
#else
            float x = (2 * (i + 0.5) / (float)cam.width - 1) *
                      imageAspectRatio * scale;
            float y = (1 - 2 * (j + 0.5) / (float)cam.width) * scale;
#endif
            Vec3 dir = cam.camToWorld.transformVector(Vec3(x, y, -1));
            dir.normalized();
            if (j == i) {
            }
            frameBuffer[j * cam.width + i] = castRay(orig, dir, cam);
        }
    }
    return frameBuffer;
}

int main(int argc, const char **argv) {
    uint32_t w = 156; // width
    uint32_t h = 100; // height

    Camera cam;
    cam.width = w;
    cam.height = h;
    cam.camToWorld = Mat44();
    cam.fov = 60;

    Pixel *data = render(cam);
    uint32_t stride = w * sizeof(Pixel);

    stbi_write_png(argv[1], w, h, 3, data, stride);

    return 0;
}
