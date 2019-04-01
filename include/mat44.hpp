#pragma once
#include "vec3.hpp"
#include <string>
/*
static Mat44 scale(Vec3 scaleBy);
static Mat44 translate(Vec3 translateBy);
static Mat44 rotate(float pitch, float yaw, float roll);
static Mat44 rotate(float angle, Vec3 axis);
Mat44(); // identity
Mat44 operator*(Mat44 other) const;
Mat44 transpose() const;
Mat44 inverse() const;
Vec3 transformVector(Vec3 vec) const;
Vec3 transformPoint(Vec3 point) const;
Vec3 transformNormal(Vec3 normal) const;
*/


class Mat44 {

    public:
        float data[16]; 

        Mat44(); // identity
        Mat44(float[]);
        static Mat44 scale(Vec3);
        static Mat44 translate(Vec3);
        static Mat44 rotatePitch(float);
        static Mat44 rotateYaw(float);
        static Mat44 rotateRoll(float);
        static Mat44 rotate(float,Vec3);

        Mat44 operator*(Mat44) const;
        bool operator==(Mat44) const;
        bool operator!=(Mat44) const;
        std::string toString() const;
        Mat44 transpose() const;
        Mat44 inverse() const;

        Vec3 transformVector(Vec3) const;
        Vec3 transformPoint(Vec3) const;
        Vec3 transformNormal(Vec3) const;
};
