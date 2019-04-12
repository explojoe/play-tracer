#include "sphere.hpp"
#include "object.hpp"
#include <iostream>

Sphere::Sphere(const Mat44 m) : objectToWorld(m), worldToObject(m.inverse()) {}

bool Sphere::intersect(const Vec3 orig, const Vec3 dir, float &t) const {
    float t0, t1; // solutions for t if intersection found.

    Vec3 orig2 = worldToObject.transformPoint(orig);
    Vec3 dir2 = worldToObject.transformVector(dir);

    Vec3 L = -orig2;
    float tca = dot(L, dir2) / dir2.magnitude(); // scalar projection
    float d2 = dot(L, L) - tca * tca;
    if (d2 > 1) {
        return false;
    }
    float thc = sqrt(1 - d2);
    t0 = tca - thc;
    t1 = tca + thc;

    if (t0 > t1) {
        std::swap(t0, t1);
    }
    if (t0 < 0) {
        t0 = t1; // if t0 is negative use t1 instead
        if (t0 < 0) {
            return false; // both are negative, no intersection
        }
    }
    t = t0/dir2.magnitude();
    return true;
}

void Sphere::getSurfaceInfo(const Vec3 pHit, Vec3 &nHit, Vec2 &tex) const {
    Vec3 pHit2 = worldToObject.transformPoint(pHit);
    nHit = pHit2.normalized();

    tex.x = (1 + atan2(nHit.z, nHit.x) / M_PI) * 0.5;
    tex.y = acosf(nHit.y) / M_PI;
    nHit = objectToWorld.transformNormal(nHit);
}
