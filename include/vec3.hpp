#pragma once
#include <string>
class Vec3 {
    public:
        float x;
        float y;
        float z;
        
        Vec3();
        Vec3(float, float, float);

        float magnitude() const;
        Vec3 normalized() const;

        Vec3 operator+(const Vec3) const; 
        Vec3 operator-(const Vec3) const;
        Vec3 operator*(const float) const;
        Vec3 operator/(const float) const;
        Vec3 operator-() const;
        bool operator==(const Vec3) const;
        bool operator!=(const Vec3) const;
        std::string toString() const;
};

Vec3 operator*(const float, const Vec3);
float dot(const Vec3, const Vec3);
Vec3 cross(const Vec3, const Vec3);
