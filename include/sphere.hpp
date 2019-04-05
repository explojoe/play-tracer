#pragma once
#include "object.hpp"
#include "mat44.hpp"
#include <cmath>

class Sphere : public Object {
    public:
        Mat44 objectToWorld;
        Mat44 worldToObject;

        Sphere(const Mat44 m);
        bool intersect(const Vec3, const Vec3, float&) const;
        void getSurfaceInfo(const Vec3, Vec3 &) const;
};
