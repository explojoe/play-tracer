#pragma once
#include "vec3.hpp"

class Ray {
    public:
        Vec3 orig;
        Vec3 dir;

        Ray();
        Ray(const Vec3,const Vec3);
};
