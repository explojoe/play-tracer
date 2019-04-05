#pragma once
#include "vec3.hpp"
#include <string>

class Mat44 {

    public:
        float data[16]; 

        Mat44(); // identity
        Mat44(const float[]);
        static Mat44 scale(const Vec3);
        static Mat44 translate(const Vec3);
        static Mat44 rotatePitch(const float);
        static Mat44 rotateYaw(const float);
        static Mat44 rotateRoll(const float);
        static Mat44 rotate(const float, const Vec3);

        Mat44 operator*(const Mat44) const;
        bool operator==(const Mat44) const;
        bool operator!=(const Mat44) const;
        std::string toString() const;
        Mat44 transpose() const;
        Mat44 inverse() const;

        Vec3 transformVector(const Vec3) const;
        Vec3 transformPoint(const Vec3) const;
        Vec3 transformNormal(const Vec3) const;
};
