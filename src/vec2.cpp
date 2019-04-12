#include "vec2.hpp"
#include "vec3.hpp"
#include "catch.hpp"

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}

float Vec2::magnitude() const { return sqrt(x * x + y * y); }

Vec2 Vec2::normalized() const {
    float mag = magnitude();
    float x1 = x / mag;
    float y1 = y / mag;
    return Vec2(x1, y1);
}

Vec2 Vec2::operator+(const Vec2 v) const {
    return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator-(const Vec2 v) const {
    return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::operator*(const float scalar) const {
    return Vec2(x * scalar, y * scalar);
}

Vec2 Vec2::operator/(const float scalar) const {
    return (*this) * (1.0 / scalar);
}

Vec2 Vec2::operator-() const { return Vec2(-x, -y); }

bool Vec2::operator==(const Vec2 v) const {
    return (x == v.x && y == v.y);
}

bool Vec2::operator!=(const Vec2 v) const { return !((*this) == v); }

std::string Vec2::toString() const {
    std::string s;
    s += "<" + std::to_string(x) + ", " + std::to_string(y) + ">";
    return s;
}

Vec2 operator*(const float scalar, Vec2 v) {
    return Vec2(v.x * scalar, v.y * scalar);
}

float dot(const Vec2 v1, const Vec2 v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

Vec3 embedCross(const Vec2 v1, const Vec2 v2) {
    float z = v1.x * v2.y - v1.y * v2.x;
    return Vec3(0, 0, z);
}

TEST_CASE("Dot products are computed", "[Vec2]") {
    REQUIRE(dot(Vec2(1, 2), Vec2()) == 0);
}

TEST_CASE("Cross products are computed", "[Vec2]") {
    REQUIRE(embedCross(Vec2(1, 2), Vec2(3, 2)) !=
            embedCross(Vec2(3, 2), Vec2(1, 2)));
}

TEST_CASE("Normalization is checked", "[Vec2]") {
    REQUIRE(Vec2(3, 4).normalized().magnitude() ==
            Vec2(0, 5).normalized().magnitude());
}
