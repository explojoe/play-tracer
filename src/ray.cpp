#include "ray.hpp"

Ray::Ray() : orig(Vec3()), dir(Vec3(0, 0, -1)) {}

Ray::Ray(const Vec3 o, const Vec3 d) : orig(o), dir(d) {}
