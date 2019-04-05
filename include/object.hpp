#pragma once
#include "vec3.hpp"

class Object {
    public:
        Vec3 color;

        virtual bool intersect(const Vec3, const Vec3, float&) const = 0;
        virtual void getSurfaceInfo(const Vec3,Vec3&) const = 0;

};
