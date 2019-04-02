#include "vec3.hpp"
#include "catch.hpp"

Vec3::Vec3() : x(0), y(0), z(0) {}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

float Vec3::magnitude() const { return sqrt(x * x + y * y + z * z); }

Vec3 Vec3::normalized() const {
    float mag = magnitude();
    float x1 = x / mag;
    float y1 = y / mag;
    float z1 = z / mag;
    return Vec3(x1, y1, z1);
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

bool Vec3::operator==(const Vec3 v) const {
    return (x == v.x && y == v.y && z == v.z);
}

bool Vec3::operator!=(const Vec3 v) const { return !((*this) == v); }

std::string Vec3::toString() const {
    std::string s;
    s += "<" + std::to_string(x) + ", " + std::to_string(y) + ", " +
         std::to_string(z) + ">";
    return s;
}

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

TEST_CASE("Cross products are computed", "[Vec3]") {
    REQUIRE(cross(Vec3(1, 2, 3), Vec3(3, 2, 1)) !=
            cross(Vec3(3, 2, 1), Vec3(1, 2, 3)));
}

TEST_CASE("Normalization is checked", "[Vec3]") {
    REQUIRE(Vec3(0, 3, 4).normalized().magnitude() ==
            Vec3(0, 0, 5).normalized().magnitude());
}
