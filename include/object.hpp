#pragma once
#include "vec3.hpp"
#include "vec2.hpp"

class Object {
    public:
        Vec3 color;

        virtual bool intersect(const Vec3, const Vec3, float&) const = 0;
        virtual void getSurfaceInfo(const Vec3, Vec3&, Vec2 &) const = 0;

};
