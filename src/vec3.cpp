#include "vec3.hpp"
#include "catch.hpp"

Vec3::Vec3() {
    x = 0;
    y = 0;
    z = 0;
}

Vec3::Vec3(float x1, float y1, float z1) {
    x = x1;
    y = y1;
    z = z1;
}

Vec3 Vec3::operator+(const Vec3 v) const {
    return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-(const Vec3 v) const {
    return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3 Vec3::operator*(const float scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::operator/(const float scalar) const {
    return (*this) * (1.0 / scalar);
}

Vec3 Vec3::operator-() const { return Vec3(-x, -y, -z); }

Vec3 operator*(const float scalar, Vec3 v) {
    return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

float dot(const Vec3 v1, const Vec3 v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3 cross(const Vec3 v1, const Vec3 v2) {
    float x = v1.y * v2.z - v1.z * v2.y;
    float y = -(v1.x * v2.z - v1.z * v2.x);
    float z = v1.x * v2.y - v1.y * v2.x;
    return Vec3(x, y, z);
}

TEST_CASE("Dot products are computed", "[Vec3]") {
    REQUIRE(dot(Vec3(1, 2, 3), Vec3()) == 0);
}
