#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "catch.hpp"
#include "mat44.hpp"
#include "object.hpp"
#include "ray.hpp"
#include "sphere.hpp"
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

const float kInfinity = std::numeric_limits<float>::max();

// clamps value to low <= value <= high
inline float clamp(const float &low, const float &high, const float &value) {
    return std::max(low, std::min(high, value));
}

// converts from degrees to radians
inline float deg2rad(const float &deg) { return deg * M_PI / 180; }

bool trace(const Vec3 &orig, const Vec3 &dir,
           const std::vector<Object *> &objects, float &tNear,
           Object **hitObject) {
    tNear = kInfinity;
    for (auto iter : objects) {
        float t = kInfinity;
        if (iter->intersect(orig, dir, t) && t < tNear) {
            *hitObject = iter;
            tNear = t;
        }
    }
    return (*hitObject != nullptr);
}

Pixel castRay(const Vec3 &orig, const Vec3 &dir, Camera &cam,
              const std::vector<Object *> &objects) {
    Vec3 hitColor = Vec3(0, 0, 0);
    Object *hitObject = nullptr;
    float t;
    if (trace(orig, dir, objects, t, &hitObject)) {
        Vec3 pHit = orig + dir * t;
        Vec3 nHit;
        hitObject->getSurfaceInfo(pHit, nHit);
        float num = dot(nHit.normalized(), (-dir).normalized());
        float num2 = num;
        Vec3 arrow = num2*(dir.normalized());
        hitColor = hitObject->color;
        hitColor = hitColor.normalized() * num;
    }
    Pixel hit;
    hit.r = 255 * clamp(0, 1, hitColor.x);
    hit.g = 255 * clamp(0, 1, hitColor.y);
    hit.b = 255 * clamp(0, 1, hitColor.z);
    return hit;
}

Pixel *render(Camera &cam, std::vector<Object *> &objects) {
    Pixel *frameBuffer = new Pixel[cam.width * cam.height];
    float scale = tan(deg2rad(cam.fov * 0.5));
    float imageAspectRatio = cam.width / (float)cam.height;
    Vec3 orig = cam.camToWorld.transformPoint(Vec3());

    for (uint32_t j = 0; j < cam.height; j++) {
        for (uint32_t i = 0; i < cam.width; i++) {
            float x = (2 * (i + 0.5) / (float)cam.width - 1) *
                      imageAspectRatio * scale;
            float y = (1 - 2 * (j + 0.5) / (float)cam.width) * scale;
            Vec3 dir = cam.camToWorld.transformVector(Vec3(x, y, -1));
            dir.normalized();
            if (j == i) {
            }
            frameBuffer[j * cam.width + i] = castRay(orig, dir, cam, objects);
        }
    }
    return frameBuffer;
}

int main(int argc, const char **argv) {
    uint32_t w = 400; // width
    uint32_t h = 400; // height

    Camera cam;
    cam.width = w;
    cam.height = h;
    cam.camToWorld = Mat44();
    cam.fov = 60;

    std::vector<Object *> objects;
    Mat44 objectWorldMat = Mat44();
    objectWorldMat = Mat44::translate(Vec3(0, 0, -3));
    objects.push_back(new Sphere(objectWorldMat));
    objects[0]->color = Vec3(100, 255, 50);

    objects.push_back(new Sphere(Mat44::translate(Vec3(-2, -2, -8))));
    objects[1]->color = Vec3(255, 100, 50);

    Pixel *data = render(cam, objects);
    uint32_t stride = w * sizeof(Pixel);

    stbi_write_png(argv[1], w, h, 3, data, stride);

    return 0;
}
