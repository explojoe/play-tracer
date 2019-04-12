#pragma once
#include <string>
#include "vec3.hpp"
class Vec2 {
    public:
        float x;
        float y;
        
        Vec2();
        Vec2(float, float);

        float magnitude() const;
        Vec2 normalized() const;

        Vec2 operator+(const Vec2) const; 
        Vec2 operator-(const Vec2) const;
        Vec2 operator*(const float) const;
        Vec2 operator/(const float) const;
        Vec2 operator-() const;
        bool operator==(const Vec2) const;
        bool operator!=(const Vec2) const;
        std::string toString() const;
};

Vec2 operator*(const float, const Vec2);
float dot(const Vec2, const Vec2);
Vec3 embedCross(const Vec2, const Vec2);
